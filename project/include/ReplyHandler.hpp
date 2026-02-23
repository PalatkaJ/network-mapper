#ifndef REPLY_HANDLER_HPP
#define REPLY_HANDLER_HPP
#include <Packet.h>

#include "Logger.hpp"

namespace netmap {
    class ReplyHandler {
        Logger& logger_;
    public:
        explicit ReplyHandler(Logger& logger);
        void ProcessArpReply(const pcpp::Packet& parsedPacket) const;
    };
}

#endif //REPLY_HANDLER_HPP
