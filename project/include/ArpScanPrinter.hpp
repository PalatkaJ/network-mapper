#ifndef NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#define NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "PcapLiveDeviceWrapper.hpp"
#include "ResultPrinter.hpp"

namespace netmap {
    class ArpScanPrinter: ResultPrinter {
        PcapLiveDeviceWrapper dev_wrapper_;
        std::vector<ArpDeviceInfo> arp_devices_found_;

    public:
        ArpScanPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger);
        void Print() const override;
    };
}

#endif //NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP