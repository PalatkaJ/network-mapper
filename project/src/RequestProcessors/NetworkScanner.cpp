#include "RequestProcessors/NetworkScanner.hpp"

#include <iostream>
#include <PcapLiveDeviceList.h>

void netmap::NetworkScanner::PrintInterfaceInformation(const pcpp::PcapLiveDevice &iface) {
    std::cout
            << "Interface info:" << std::endl
            << "   Interface IPv4:        " << iface.getIPv4Address() << std::endl
            << "   Interface name:        " << iface.getName() << std::endl
            << "   Interface description: " << iface.getDesc() << std::endl
            << "   MAC address:           " << iface.getMacAddress() << std::endl
            << "   Default gateway:       " << iface.getDefaultGateway() << std::endl
            << "   Interface MTU:         " << iface.getMtu() << std::endl;

    if (!iface.getDnsServers().empty()) {
        std::cout << "   DNS server:            " << iface.getDnsServers().front() << std::endl;
    }
}

netmap::NetworkScanner::NetworkScanner(ScanRequest &&scan_request): scan_request_(std::move(scan_request)) {
}

void netmap::NetworkScanner::Process() {
    auto *dev = pcpp::PcapLiveDeviceList::getInstance().getDeviceByName(scan_request_.interface_name);
    if (dev == nullptr) {
        throw std::runtime_error("Cannot find interface");
    }

    PrintInterfaceInformation(*dev);
}
