#include "ArpDeviceInfo.hpp"

netmap::ArpDeviceInfo::ArpDeviceInfo(pcpp::MacAddress mac, pcpp::IPv4Address ip, std::string vendorName)
    :mac_(mac), ip_(ip), vendor_name_(std::move(vendorName)) {}