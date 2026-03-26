#ifndef DEV_WRAPPER_FOR_TRACEROUTE_HPP
#define DEV_WRAPPER_FOR_TRACEROUTE_HPP
#include <PcapLiveDevice.h>

namespace netmap {
    struct DevWrapperForTraceroute {
        pcpp::PcapLiveDevice *device;
        const pcpp::MacAddress gateway_mac;

        DevWrapperForTraceroute(pcpp::PcapLiveDevice *device, const pcpp::MacAddress gateway_mac);
    };

    inline pcpp::IPv4Address operator&(const pcpp::IPv4Address& a1, const pcpp::IPv4Address& a2) {
        return {a1.toInt() & a2.toInt()};
    }
}

#endif //DEV_WRAPPER_FOR_TRACEROUTE_HPP