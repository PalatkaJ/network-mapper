#ifndef ARP_SCAN_PRINTER_HPP
#define ARP_SCAN_PRINTER_HPP
#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "DevWrapperForArpScan.hpp"
#include "ResultPrinter.hpp"

namespace netmap {
    class ArpScanPrinter: public ResultPrinter {
        DevWrapperForArpScan dev_wrapper_;
        std::vector<ArpDeviceInfo> arp_devices_found_;

    protected:
        void PrintBody(std::stringstream &ss) const override;
        void PrintHeader(std::stringstream &ss) const override;
        [[nodiscard]] inline std::string GetTitle() const override;
    public:
        ArpScanPrinter(DevWrapperForArpScan dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger, PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string ArpScanPrinter::GetTitle() const {
        return " ARP Scan Results";
    }
}

#endif //ARP_SCAN_PRINTER_HPP