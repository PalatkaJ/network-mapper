#ifndef NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP
#define NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP
#include <IcmpLayer.h>
#include <IpAddress.h>
#include <Packet.h>

#include "Logger.hpp"

namespace netmap {
    class IcmpReplyHandler {
        Logger& logger_;
        std::vector<pcpp::IPv4Address> hit_ips_;
        bool dest_hit_ = false;

        void ProcessIcmpReply(const pcpp::IcmpLayer *icmp_layer);
        void ProcessEchoReply(const pcpp::IcmpLayer *icmp_layer);
        void ProcessTimeExceeded(const pcpp::IcmpLayer *icmp_layer);

    public:
        explicit IcmpReplyHandler(Logger& logger);
        void ProcessIcmpReply(const pcpp::Packet& parsedPacket);

        [[nodiscard]] const std::vector<pcpp::IPv4Address>& GetHitIps() const;
        [[nodiscard]] bool IsDestHit() const;
    };

    inline const std::vector<pcpp::IPv4Address>& IcmpReplyHandler::GetHitIps() const {
        return hit_ips_;
    }

    inline bool IcmpReplyHandler::IsDestHit() const {
        return dest_hit_;
    }
}

#endif //NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP