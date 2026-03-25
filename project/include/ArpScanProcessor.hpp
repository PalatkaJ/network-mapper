#ifndef INTERFACE_SCANNING_PROCESSOR_H
#define INTERFACE_SCANNING_PROCESSOR_H
#include <ifaddrs.h>
#include <PcapLiveDevice.h>

#include "RequestProcessor.hpp"
#include "UserRequest.hpp"
#include "PcapLiveDeviceWrapper.hpp"

namespace netmap {
    class ArpScanProcessor final : public RequestProcessor {
        const UserRequest &user_request_;
        Logger& logger_;

        static bool IsTargetIfa(const ifaddrs *ifa, const std::string& devName);
        static pcpp::IPv4Address GetDeviceNetmask(const pcpp::PcapLiveDevice& dev);

    public:
        explicit ArpScanProcessor(const UserRequest &user_request, Logger& logger);

        void Process() override;
    };
}


#endif //INTERFACE_SCANNING_PROCESSOR_H
