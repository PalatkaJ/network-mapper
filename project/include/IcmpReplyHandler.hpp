#ifndef NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP
#define NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP
#include <Packet.h>

#include "Logger.hpp"

namespace netmap {
    class IcmpReplyHandler {
        Logger& logger_;
    public:
        explicit IcmpReplyHandler(Logger& logger);
        void ProcessIcmpReply(const pcpp::Packet& parsedPacket);
    };
}

#endif //NETWORK_MAPPER_ICMP_REPLY_HANDLER_HPP