
#ifndef ARP_DEVICE_INFO_HPP
#define ARP_DEVICE_INFO_HPP
#include <IpAddress.h>
#include <MacAddress.h>

namespace netmap {
    class ArpDeviceInfo {
        pcpp::MacAddress mac_;
        pcpp::IPv4Address ip_;
        std::string vendor_name_;
    public:
        ArpDeviceInfo(pcpp::MacAddress mac, pcpp::IPv4Address ip, std::string vendorName);

        [[nodiscard]] const pcpp::MacAddress& GetMacAddress() const;
        [[nodiscard]] const pcpp::IPv4Address& GetIPAddress() const;
        [[nodiscard]] const std::string& GetVendorName() const;
    };

    inline const pcpp::MacAddress& ArpDeviceInfo::GetMacAddress() const {
        return mac_;
    }

    inline const pcpp::IPv4Address& ArpDeviceInfo::GetIPAddress() const {
        return ip_;
    }

    inline const std::string& ArpDeviceInfo::GetVendorName() const {
        return vendor_name_;
    }
}

#endif //ARP_DEVICE_INFO_HPP