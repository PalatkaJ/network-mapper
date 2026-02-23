#ifndef ARPSCANNER_HPP
#define ARPSCANNER_HPP
#include <iostream>

#include "Logger.hpp"
#include "PcapLiveDeviceWrapper.hpp"


namespace netmap {
    class ArpScanner {
    private:
        PcapLiveDeviceWrapper& wrappedDev_;
        Logger& logger_;
        ScanRequest scan_request_;

        [[nodiscard]] pcpp::IPv4Address GetStartingIpAddress() const;
        static void IncrementIpAddress(pcpp::IPv4Address& ip);
        void BuildAndSendArpPacket(const pcpp::IPv4Address& ip) const;
        static uint32_t GetHostIntFromNetIp(const pcpp::IPv4Address& ip);

        void SendArpRequests() const;
        void PrepareDeviceForArpCapture() const;
        static void OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie);

    public:
        explicit ArpScanner(PcapLiveDeviceWrapper& wrappedDev, Logger& logger, ScanRequest scan_request);

        void ScanNetwork() const;
    };
}


#endif //ARPSCANNER_HPP
