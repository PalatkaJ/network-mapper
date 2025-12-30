#ifndef REPLY_HANDLER_HPP
#define REPLY_HANDLER_HPP
#include <Packet.h>

namespace netmap {
    class ReplyHandler {
    public:
        void ProcessArpReply(const pcpp::Packet& parsedPacket) const;
    };

}

#endif //REPLY_HANDLER_HPP
