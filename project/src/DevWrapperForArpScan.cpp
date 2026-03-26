#include "DevWrapperForArpScan.hpp"

netmap::DevWrapperForArpScan::DevWrapperForArpScan(pcpp::PcapLiveDevice *device, const pcpp::IPv4Address netmask)
    : device(device), netmask(netmask) {}

