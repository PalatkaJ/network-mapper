#include "ArpScanPrinter.hpp"

#include <iomanip>

#include "Logger.hpp"

netmap::ArpScanPrinter::ArpScanPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger)
    : dev_wrapper_(dev_wrapper), arp_devices_found_(std::move(arp_devices_found)), ResultPrinter(logger) {}

void netmap::ArpScanPrinter::Print() const {
    // TODO this will need a big refactor, I should be able to write just stream << ArpDeviceInfo, so overload operator, define constants and so on...
    std::stringstream ss;

    ss << "\n" << std::string(80, '=') << "\n";
    ss << " NETWORK SCAN REPORT\n";
    ss << " Interface: " << (dev_wrapper_.device ? dev_wrapper_.device->getName() : "Unknown") << "\n";
    ss << " IPv4 Addr: " << (dev_wrapper_.device ? dev_wrapper_.device->getIPv4Address().toString() : "N/A") << "\n";
    ss << " Netmask:   " << dev_wrapper_.netmask.toString() << "\n";
    ss << std::string(80, '-') << "\n";

    if (arp_devices_found_.empty()) {
        ss << " No devices found in the network.\n";
    } else {
        const int ip_width = 16;
        const int mac_width = 18;

        ss << std::left
           << std::setw(ip_width)  << " IP Address"
           << std::setw(mac_width) << " MAC Address"
           << " Vendor\n";

        ss << std::string(80, '-') << "\n";

        for (const auto& device : arp_devices_found_) {
            ss << " "
               << std::setw(ip_width - 1)  << device.GetIPAddress().toString()
               << std::setw(mac_width) << device.GetMacAddress().toString()
               << device.GetVendorName() << "\n";
        }
    }

    ss << std::string(80, '=') << "\n";

    logger_.Log(ss.str());
}


