#ifndef ICMP_REPLY_HANDLER_HPP
#define ICMP_REPLY_HANDLER_HPP
#include <IcmpLayer.h>
#include <IpAddress.h>
#include <Packet.h>
#include <array>
#include <mutex>

#include "Logger.hpp"
#include "NetworkConstants.hpp"

namespace netmap {
    class IcmpReplyHandler {
        Logger& logger_;
        std::array<pcpp::IPv4Address, MAX_HOPS> hit_ips_;

        bool dest_hit_ = false;

        void ProcessIcmpReply(pcpp::IcmpLayer *icmp_layer);
        void ProcessEchoReply(pcpp::IcmpLayer *icmp_layer);

        void ProcessTimeExceeded(const pcpp::IcmpLayer *icmp_layer);

    public:

        std::mutex mutex_;
        std::condition_variable cv_;

        explicit IcmpReplyHandler(Logger& logger);
        void ProcessIcmpReply(const pcpp::Packet& parsedPacket);

        [[nodiscard]] const std::array<pcpp::IPv4Address, MAX_HOPS>& GetHitIps() const;
        [[nodiscard]] bool IsDestHit() const;
        [[nodiscard]] std::condition_variable& GetCondVar();
        [[nodiscard]] std::mutex& GetMutex();
    };

    inline const std::array<pcpp::IPv4Address, MAX_HOPS>& IcmpReplyHandler::GetHitIps() const {
        return hit_ips_;
    }

    inline bool IcmpReplyHandler::IsDestHit() const {
        return dest_hit_;
    }

    inline std::mutex& IcmpReplyHandler::GetMutex() {
        return mutex_;
    }

    inline std::condition_variable& IcmpReplyHandler::GetCondVar() {
        return cv_;
    }

}

#endif //ICMP_REPLY_HANDLER_HPP