#ifndef INTERFACE_OPTION_HANDLER_HPP
#define INTERFACE_OPTION_HANDLER_HPP
#include <PcapLiveDevice.h>

#include "RequestProcessor.hpp"
#include "../Application/ScanRequest.hpp"

namespace netmap {
    class NetworkScanner final : public RequestProcessor {
    private:
        ScanRequest scan_request_;

        static void PrintInterfaceInformation(const pcpp::PcapLiveDevice &iface);

    public:
        explicit NetworkScanner(ScanRequest&& scan_request);

        void Process() override;
    };
}


#endif //INTERFACE_OPTION_HANDLER_HPP
