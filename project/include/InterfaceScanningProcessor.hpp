#ifndef INTERFACE_SCANNING_PROCESSOR_H
#define INTERFACE_SCANNING_PROCESSOR_H
#include <ifaddrs.h>
#include <PcapLiveDevice.h>

#include "RequestProcessor.hpp"
#include "UserRequest.hpp"
#include "PcapLiveDeviceWrapper.hpp"

namespace netmap {
    class InterfaceScanningProcessor final : public RequestProcessor {
    private:
        UserRequest *user_request_;
        Logger& logger_;

        static bool IsInterestingIfa(const ifaddrs *ifa, const std::string& devName);
        static pcpp::IPv4Address GetDeviceNetmask(const pcpp::PcapLiveDevice& dev);

    public:
        explicit InterfaceScanningProcessor(UserRequest *user_request, Logger& logger);

        void Process() override;
    };
}


#endif //INTERFACE_SCANNING_PROCESSOR_H
