#include "InterfaceScanningProcessor.hpp"
#include "PcapLiveDeviceWrapper.hpp"
#include "ArpScanner.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"

#include <iostream>
#include <PcapLiveDeviceList.h>
#include "IpAddress.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <ifaddrs.h>
#include <format>

void netmap::InterfaceScanningProcessor::LogInterfaceInformation(const PcapLiveDeviceWrapper &wrappedDev) {

    logger_.Log("Interface info:");
    logger_.Log(std::format("   Interface IPv4:        {}", wrappedDev.device->getIPv4Address().toString()));
    logger_.Log(std::format("   Interface name:        {}", wrappedDev.device->getName()));
    logger_.Log(std::format("   Interface netmask:     {}", wrappedDev.netmask.toString()));
    logger_.Log(std::format("   Interface description: {}", wrappedDev.device->getDesc()));
    logger_.Log(std::format("   MAC address:           {}", wrappedDev.device->getMacAddress().toString()));
    logger_.Log(std::format("   Default gateway:       {}", wrappedDev.device->getDefaultGateway().toString()));
    logger_.Log(std::format("   Interface MTU:         {}", wrappedDev.device->getMtu()));

    if (!wrappedDev.device->getDnsServers().empty()) {
        logger_.Log(std::format("   DNS server:            {}", wrappedDev.device->getDnsServers().front().toString()));
    }
}

bool netmap::InterfaceScanningProcessor::IsInterestingIfa(const ifaddrs *ifa, const std::string &devName) {
    // AF_INET means IPv4, and it is the interface we were requested (by the name, e.g., eth0)
    return ifa->ifa_netmask && ifa->ifa_netmask->sa_family == AF_INET
        && strcmp(ifa->ifa_name, devName.c_str()) == 0;
}

pcpp::IPv4Address netmap::InterfaceScanningProcessor::GetDeviceNetmask(const pcpp::PcapLiveDevice &dev) {
    ifaddrs *ifap = nullptr;

    // this generates a linked list of interface devices
    // (we want to find the netmask of the ip addresses so the scanner can be efficient)
    if (getifaddrs(&ifap) != 0) {
        throw std::runtime_error("parsing network interfaces on machine failed");
    }

    // iterate the linked list of interface devices and find the one we want to sniff on
    for (const ifaddrs *ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
        if (IsInterestingIfa(ifa, dev.getName())) {
            char netmask[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in *>(ifa->ifa_netmask)->sin_addr,
                    netmask, INET_ADDRSTRLEN);

            freeifaddrs(ifap);
            return {netmask};
        }
    }

    freeifaddrs(ifap);

    // nothing sensible to do
    throw std::runtime_error("couldn't find netmask for given interface");
}

netmap::InterfaceScanningProcessor::InterfaceScanningProcessor(ScanRequest &&scan_request, Logger &logger)
    :scan_request_(std::move(scan_request)), logger_(logger) {}

void netmap::InterfaceScanningProcessor::Process() {
    logger_.VerboseLog(std::format("Trying to find interface {}", scan_request_.interface_name));

    auto *dev = pcpp::PcapLiveDeviceList::getInstance().getDeviceByName(scan_request_.interface_name);
    if (dev == nullptr) {
        throw std::runtime_error("Cannot find interface");
    }

    logger_.VerboseLog(std::format("Interface {} found", dev->getName()));

    const auto netmask = GetDeviceNetmask(*dev);

    // wrap the device so it contains the netmask as well
    PcapLiveDeviceWrapper wrappedDev(dev, netmask);

    LogInterfaceInformation(wrappedDev);

    auto mac_vendor_mapper = MacVendorMapper{"mac-vendors-export.csv", logger_};
    mac_vendor_mapper.Map();
    auto arp_scanner = ArpScanner{wrappedDev, mac_vendor_mapper, logger_, std::move(scan_request_)};

    arp_scanner.ScanNetwork();
}
