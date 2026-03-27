
#ifndef ARP_DEVICE_INFO_HPP
#define ARP_DEVICE_INFO_HPP

#include <IpAddress.h>
#include <MacAddress.h>
#include <string>



namespace netmap {
    /**
     * @brief Represents a device discovered on the network via an ARP scan.
     *
     * This class stores the essential information about a network device, including
     * its MAC address, IPv4 address, and the vendor name associated with its MAC address.
     */
    class ArpDeviceInfo {
        pcpp::MacAddress mac_;
        pcpp::IPv4Address ip_;
        std::string vendor_name_;

    public:
        /**
         * @brief Constructs an ArpDeviceInfo object.
         * @param mac The MAC address of the device.
         * @param ip The IPv4 address of the device.
         * @param vendorName The vendor name, as determined from the MAC address.
         */
        ArpDeviceInfo(pcpp::MacAddress mac, pcpp::IPv4Address ip, std::string vendorName);

        /**
         * @brief Gets the MAC address of the device.
         * @return A constant reference to the pcpp::MacAddress object.
         */
        [[nodiscard]] const pcpp::MacAddress &GetMacAddress() const;

        /**
         * @brief Gets the IPv4 address of the device.
         * @return A constant reference to the pcpp::IPv4Address object.
         */
        [[nodiscard]] const pcpp::IPv4Address &GetIPAddress() const;

        /**
         * @brief Gets the vendor name of the device's network interface.
         * @return A constant reference to the vendor name string.
         */
        [[nodiscard]] const std::string &GetVendorName() const;
    };

    inline const pcpp::MacAddress &ArpDeviceInfo::GetMacAddress() const {
        return mac_;
    }

    inline const pcpp::IPv4Address &ArpDeviceInfo::GetIPAddress() const {
        return ip_;
    }

    inline const std::string &ArpDeviceInfo::GetVendorName() const {
        return vendor_name_;
    }
}


#endif //ARP_DEVICE_INFO_HPP
