#ifndef REPLY_HANDLER_HPP
#define REPLY_HANDLER_HPP
#include <Packet.h>

#include "ArpDeviceInfo.hpp"
#include "app/Logger.hpp"
#include "MacVendorMapper.hpp"

#include <vector>

namespace netmap {
    constexpr size_t ARP_DEV_RESERVE = 254;

    /**
     * @brief Processes ARP reply packets to identify and store device information.
     *
     * This class is designed to be used within a packet capture callback. It parses
     * ARP reply packets, extracts device details (IP, MAC), looks up the vendor,
     * and accumulates a list of discovered devices.
     */
    class ArpReplyHandler {
        std::vector<ArpDeviceInfo> devices_;
        MacVendorMapper &mac_vendor_mapper_;
        Logger &logger_;

    public:
        /**
         * @brief Constructs an ArpReplyHandler.
         * @param mac_vendor_mapper A mapper to resolve MAC addresses to vendor names.
         * @param logger A logger for logging messages.
         */
        explicit ArpReplyHandler(MacVendorMapper &mac_vendor_mapper, Logger &logger);

        /**
         * @brief Processes a single ARP reply packet.
         * @param parsedPacket The packet to be processed.
         */
        void ProcessArpReply(const pcpp::Packet &parsedPacket);

        /**
         * @brief Retrieves the list of discovered devices.
         *
         * This method moves the internal list of devices to the caller.
         * @return A vector of ArpDeviceInfo objects.
         */
        std::vector<ArpDeviceInfo> StealArpDevices();
    };

    inline std::vector<ArpDeviceInfo> ArpReplyHandler::StealArpDevices() {
        return std::move(devices_);
    }
}

#endif //REPLY_HANDLER_HPP
