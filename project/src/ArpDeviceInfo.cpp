#include "ArpDeviceInfo.hpp"

netmap::ArpDeviceInfo::ArpDeviceInfo(pcpp::MacAddress mac, pcpp::IPAddress ip, std::string vendorName)
    :mac_(mac), ip_(ip), vendor_name_(std::move(vendorName)) {}