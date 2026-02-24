#ifndef REPLY_HANDLER_HPP
#define REPLY_HANDLER_HPP
#include <Packet.h>

#include "Logger.hpp"
#include "MacVendorMapper.hpp"

namespace netmap {
    class ReplyHandler {
        MacVendorMapper& mac_vendor_mapper_;
        Logger& logger_;
    public:
        explicit ReplyHandler(MacVendorMapper& mac_vendor_mapper, Logger& logger);
        void ProcessArpReply(const pcpp::Packet& parsedPacket) const;
    };
}

#endif //REPLY_HANDLER_HPP
