#ifndef ARP_SCAN_PROCESSOR_HPP
#define ARP_SCAN_PROCESSOR_HPP
#include <ifaddrs.h>
#include <PcapLiveDevice.h>

#include "RequestProcessor.hpp"
#include "UserRequest.hpp"
#include "DevWrapperForArpScan.hpp"

namespace netmap {
    class ArpScanProcessor final : public RequestProcessor {
        const UserRequest &user_request_;

        static bool IsTargetIfa(const ifaddrs *ifa, const std::string& devName);
        static pcpp::IPv4Address GetDeviceNetmask(const pcpp::PcapLiveDevice& dev);

    public:
        explicit ArpScanProcessor(const UserRequest &user_request, Logger& logger);

        void Process() override;
    };
}


#endif //ARP_SCAN_PROCESSOR_HPP
