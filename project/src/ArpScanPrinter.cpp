#include "ArpScanPrinter.hpp"

#include <iomanip>

#include "Logger.hpp"

netmap::ArpScanPrinter::ArpScanPrinter(PcapLiveDeviceWrapper dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger& logger)
    : dev_wrapper_(dev_wrapper), arp_devices_found_(std::move(arp_devices_found)), ResultPrinter(logger) {}

void netmap::ArpScanPrinter::PrintHeader(std::stringstream& ss, size_t width, const char main_sep, const char sub_sep) const {
    ss << " NETWORK SCAN REPORT" << std::endl;
    ss << std::string(width, main_sep) << std::endl;
    ss << " Interface: " << (dev_wrapper_.device ? dev_wrapper_.device->getName() : "Unknown") << std::endl;
    ss << " IPv4 Addr: " << (dev_wrapper_.device ? dev_wrapper_.device->getIPv4Address().toString() : "N/A") << std::endl;
    ss << " Netmask:   " << dev_wrapper_.netmask.toString() << std::endl;
    ss << std::string(width, sub_sep) << std::endl;
}

void netmap::ArpScanPrinter::PrintBody(std::stringstream& ss, const size_t width, const char sub_sep) const {
    if (arp_devices_found_.empty()) {
        ss << " No devices found in the network." << std::endl;
    } else {
        const size_t ip_width = 16;
        const size_t mac_width = 18;

        ss << std::left
                << std::setw(ip_width)  << " IP Address"
                << std::setw(mac_width) << " MAC Address"
                << " Vendor" << std::endl;

        ss << std::string(width, sub_sep) << std::endl;

        for (const auto& device : arp_devices_found_) {
            ss << " "
                    << std::setw(ip_width - 1)  << device.GetIPAddress().toString()
                    << std::setw(mac_width) << device.GetMacAddress().toString()
                    << device.GetVendorName() << std::endl;
        }
    }
}

void netmap::ArpScanPrinter::Print() const {
    std::stringstream ss;
    const size_t width = 80;
    const char main_sep = '=';
    const char sub_sep = '-';

    PrintHeader(ss, width, main_sep, sub_sep);

    PrintBody(ss, width, sub_sep);

    ss << std::string(width, main_sep) << std::endl;

    logger_.Log(ss.str());
}


