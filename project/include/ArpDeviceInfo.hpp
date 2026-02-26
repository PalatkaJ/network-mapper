//
// Created by Jan Palatka on 26.02.2026.
//

#ifndef NETWORK_MAPPER_ARP_DEVICE_INFO_HPP
#define NETWORK_MAPPER_ARP_DEVICE_INFO_HPP
#include <IpAddress.h>
#include <MacAddress.h>

namespace netmap {
    class ArpDeviceInfo {
        pcpp::MacAddress mac_;
        pcpp::IPAddress ip_;
        std::string vendor_name_;
    public:
        ArpDeviceInfo(pcpp::MacAddress mac, pcpp::IPAddress ip, std::string vendorName);

        pcpp::MacAddress GetMacAddress() const;
        pcpp::IPAddress GetIPAddress() const;
        std::string GetVendorName() const;
    };

    inline pcpp::MacAddress ArpDeviceInfo::GetMacAddress() const {
        return mac_;
    }

    inline pcpp::IPAddress ArpDeviceInfo::GetIPAddress() const {
        return ip_;
    }

    inline std::string ArpDeviceInfo::GetVendorName() const {
        return vendor_name_;
    }
}

#endif //NETWORK_MAPPER_ARP_DEVICE_INFO_HPP