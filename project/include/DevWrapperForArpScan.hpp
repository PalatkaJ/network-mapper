#ifndef DEV_WRAPPER_FOR_ARP_SCAN_HPP
#define DEV_WRAPPER_FOR_ARP_SCAN_HPP
#include <PcapLiveDevice.h>
#include <IpAddress.h>

namespace netmap {
    /**
     * @brief Wraps a network device and its netmask for ARP scanning.
     *
     * This struct conveniently bundles a pointer to a live PcapPlusPlus device
     * with its corresponding IPv4 netmask, which is essential for calculating
     * the network range for an ARP scan.
     */
    struct DevWrapperForArpScan {
        /** @brief A pointer to the live network capture device. */
        pcpp::PcapLiveDevice *device;
        /** @brief The netmask of the device's network. */
        const pcpp::IPv4Address netmask;

        /**
         * @brief Constructs a DevWrapperForArpScan.
         * @param device A pointer to the live device.
         * @param netmask The IPv4 netmask of the device.
         */
        DevWrapperForArpScan(pcpp::PcapLiveDevice *device, const pcpp::IPv4Address netmask);
    };

    /**
     * @brief Overloads the bitwise AND operator for two IPv4 addresses.
     *
     * This is useful for network address calculations, such as determining the
     * network ID from an IP address and a netmask.
     * @param a1 The first IPv4 address.
     * @param a2 The second IPv4 address.
     * @return The resulting IPv4 address after the bitwise AND operation.
     */
    inline pcpp::IPv4Address operator&(const pcpp::IPv4Address &a1, const pcpp::IPv4Address &a2) {
        return {a1.toInt() & a2.toInt()};
    }
}

#endif //DEV_WRAPPER_FOR_ARP_SCAN_HPP
