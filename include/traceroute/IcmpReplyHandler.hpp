#ifndef ICMP_REPLY_HANDLER_HPP
#define ICMP_REPLY_HANDLER_HPP

#include "app/Logger.hpp"
#include "app/NetworkConstants.hpp"

#include <IcmpLayer.h>
#include <IpAddress.h>
#include <Packet.h>
#include <array>
#include <mutex>
#include <condition_variable>


namespace netmap {
    /**
     * @brief Processes ICMP reply packets, primarily for traceroute functionality.
     *
     * This class inspects incoming ICMP packets (like Time Exceeded and Echo Reply)
     * to build a traceroute path. It also manages threading constructs (mutex and
     * condition variable) to signal when the trace is complete.
     */
    class IcmpReplyHandler {
        std::array<pcpp::IPv4Address, MAX_HOPS> hit_ips_;
        std::mutex mutex_;
        std::condition_variable cv_;
        Logger &logger_;
        bool dest_hit_ = false;

        void ProcessIcmpReply(pcpp::IcmpLayer *icmp_layer);

        void ProcessEchoReply(pcpp::IcmpLayer *icmp_layer);

        void ProcessTimeExceeded(const pcpp::IcmpLayer *icmp_layer);

    public:
        /**
         * @brief Constructs an IcmpReplyHandler.
         * @param logger A logger instance for logging messages.
         */
        explicit IcmpReplyHandler(Logger &logger);

        /**
         * @brief Processes a single ICMP reply packet.
         * @param parsedPacket The packet to process.
         */
        void ProcessIcmpReply(const pcpp::Packet &parsedPacket);

        /**
         * @brief Gets the array of IP addresses discovered at each hop.
         * @return A constant reference to the array of hop IP addresses.
         */
        [[nodiscard]] std::array<pcpp::IPv4Address, MAX_HOPS> GetHitIps() const;

        /**
         * @brief Checks if the final destination has been reached.
         * @return True if the destination has been reached, false otherwise.
         */
        [[nodiscard]] bool IsDestHit() const;

        /**
         * @brief Gets a reference to the condition variable for synchronization.
         * @return A reference to the std::condition_variable.
         */
        [[nodiscard]] std::condition_variable &GetCondVar();

        /**
         * @brief Gets a reference to the mutex for synchronization.
         * @return A reference to the std::mutex.
         */
        [[nodiscard]] std::mutex &GetMutex();
    };

    inline std::array<pcpp::IPv4Address, MAX_HOPS> IcmpReplyHandler::GetHitIps() const {
        return hit_ips_;
    }

    inline bool IcmpReplyHandler::IsDestHit() const {
        return dest_hit_;
    }

    inline std::mutex &IcmpReplyHandler::GetMutex() {
        return mutex_;
    }

    inline std::condition_variable &IcmpReplyHandler::GetCondVar() {
        return cv_;
    }
}

#endif //ICMP_REPLY_HANDLER_HPP
