#ifndef INTERFACE_SCANNING_PROCESSOR_H
#define INTERFACE_SCANNING_PROCESSOR_H
#include <ifaddrs.h>
#include <PcapLiveDevice.h>

#include "RequestProcessor.hpp"
#include "ScanRequest.hpp"
#include "PcapLiveDeviceWrapper.hpp"

namespace netmap {
    class InterfaceScanningProcessor final : public RequestProcessor {
    private:
        ScanRequest scan_request_;

        static void PrintInterfaceInformation(const PcapLiveDeviceWrapper &wrappedDev);
        static bool IsInterestingIfa(const ifaddrs *ifa, const std::string& devName);
        static pcpp::IPv4Address GetDeviceNetmask(const pcpp::PcapLiveDevice& dev);

    public:
        explicit InterfaceScanningProcessor(ScanRequest&& scan_request);

        void Process() override;
    };
}


#endif //INTERFACE_SCANNING_PROCESSOR_H
