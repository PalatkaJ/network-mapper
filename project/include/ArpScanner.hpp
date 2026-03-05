#ifndef ARPSCANNER_HPP
#define ARPSCANNER_HPP
#include <iostream>

#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"
#include "PcapLiveDeviceWrapper.hpp"


namespace netmap {
    class ArpScanner {
        PcapLiveDeviceWrapper& wrappedDev_;
        MacVendorMapper& mac_vendor_mapper_;
        Logger& logger_;
        const UserRequest &user_request_;

        [[nodiscard]] pcpp::IPv4Address GetStartingIpAddress() const;
        static void IncrementIpAddress(pcpp::IPv4Address& ip);
        void BuildAndSendArpPacket(const pcpp::IPv4Address& ip) const;
        static uint32_t GetHostIntFromNetIp(const pcpp::IPv4Address& ip);

        void SendArpRequests() const;
        void PrepareDeviceForArpCapture() const;
        static void OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie);

    public:
        explicit ArpScanner(PcapLiveDeviceWrapper& wrappedDev, MacVendorMapper& mac_vendor_mapper, Logger& logger, const UserRequest &user_request);

        std::vector<ArpDeviceInfo> ScanNetwork();
    };
}


#endif //ARPSCANNER_HPP
