#ifndef DEV_WRAPPER_FOR_ARP_SCAN_HPP
#define DEV_WRAPPER_FOR_ARP_SCAN_HPP
#include <PcapLiveDevice.h>

namespace netmap {
    struct DevWrapperForArpScan {
        pcpp::PcapLiveDevice *device;
        const pcpp::IPv4Address netmask;

        DevWrapperForArpScan(pcpp::PcapLiveDevice *device, const pcpp::IPv4Address netmask);
    };

    inline pcpp::IPv4Address operator&(const pcpp::IPv4Address& a1, const pcpp::IPv4Address& a2) {
        return {a1.toInt() & a2.toInt()};
    }
}

#endif //DEV_WRAPPER_FOR_ARP_SCAN_HPP
