#ifndef NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#define NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "PcapLiveDeviceWrapper.hpp"

namespace netmap {
    class NetworkAsciPrinter {
        PcapLiveDeviceWrapper dev_wrapper_;
        std::vector<ArpDeviceInfo> arp_devices_found_;
        Logger& logger_;

    public:
        NetworkAsciPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger);
        void PrettyPrint() const;
    };
}

#endif //NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP