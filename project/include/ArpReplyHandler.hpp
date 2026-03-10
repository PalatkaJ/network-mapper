#ifndef REPLY_HANDLER_HPP
#define REPLY_HANDLER_HPP
#include <Packet.h>

#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"

namespace netmap {
    class ArpReplyHandler {
        std::vector<ArpDeviceInfo> devices_;
        MacVendorMapper& mac_vendor_mapper_;
        Logger& logger_;
    public:
        explicit ArpReplyHandler(MacVendorMapper& mac_vendor_mapper, Logger& logger);
        void ProcessArpReply(const pcpp::Packet& parsedPacket);
        std::vector<ArpDeviceInfo> GetArpDevices();
    };

    inline std::vector<ArpDeviceInfo> ArpReplyHandler::GetArpDevices() {
        return std::move(devices_);
    }
}

#endif //REPLY_HANDLER_HPP
