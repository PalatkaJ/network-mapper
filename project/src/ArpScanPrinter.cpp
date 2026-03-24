#include "ArpScanPrinter.hpp"

#include <iomanip>

#include "Logger.hpp"

void netmap::ArpScanPrinter::PrintBody(std::stringstream &ss) const {
    if (arp_devices_found_.empty()) {
        ss << " No devices found in the network." << std::endl;
    } else {
        constexpr size_t min_ip_size = 16;
        constexpr size_t min_mac_size = 18;

        const size_t ip_width  = std::max<size_t>(min_ip_size, printer_config_.width * 0.20);
        const size_t mac_width = std::max<size_t>(min_mac_size, printer_config_.width * 0.25);

        ss << std::left
                << std::setw(ip_width)  << " IP Address"
                << std::setw(mac_width) << " MAC Address"
                << " Vendor" << std::endl;

        ss << std::string(printer_config_.width, printer_config_.sub_sep) << std::endl;

        for (const auto& device : arp_devices_found_) {
            ss << " "
                    << std::setw(ip_width - 1)  << device.GetIPAddress().toString()
                    << std::setw(mac_width) << device.GetMacAddress().toString()
                    << device.GetVendorName() << std::endl;
        }
    }
}

void netmap::ArpScanPrinter::PrintHeader(std::stringstream &ss) const {
    ss << " Interface:       " << (dev_wrapper_.device ? dev_wrapper_.device->getName() : "Unknown") << std::endl;
    ss << " IPv4 Addr:       " << (dev_wrapper_.device ? dev_wrapper_.device->getIPv4Address().toString() : "N/A") << std::endl;
    ss << " Default Gateway: " << (dev_wrapper_.device ? dev_wrapper_.device->getDefaultGateway().toString() : "N/A") << std::endl;
    ss << " Netmask:         " << dev_wrapper_.netmask.toString() << std::endl;
}

netmap::ArpScanPrinter::ArpScanPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger, PrinterConfig printer_config)
    : ResultPrinter(logger, std::move(printer_config)), dev_wrapper_(dev_wrapper), arp_devices_found_(std::move(arp_devices_found)) {}



