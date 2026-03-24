#ifndef NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#define NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP
#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "PcapLiveDeviceWrapper.hpp"
#include "ResultPrinter.hpp"

namespace netmap {
    class ArpScanPrinter: public ResultPrinter {
        PcapLiveDeviceWrapper dev_wrapper_;
        std::vector<ArpDeviceInfo> arp_devices_found_;

    protected:
        void PrintBody(std::stringstream &ss) const override;
        void PrintHeader(std::stringstream &ss) const override;
        [[nodiscard]] inline std::string GetTitle() const override;
    public:
        ArpScanPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger, PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string ArpScanPrinter::GetTitle() const {
        return " ARP Scan Results";
    }
}

#endif //NETWORK_MAPPER_NETWORK_ASCI_PRINTER_HPP