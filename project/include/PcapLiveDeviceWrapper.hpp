#ifndef PCAP_LIVE_DEVICE_WRAPPER_HPP
#define PCAP_LIVE_DEVICE_WRAPPER_HPP
#include <PcapLiveDevice.h>

namespace netmap {
    struct PcapLiveDeviceWrapper {
        pcpp::PcapLiveDevice *device;
        pcpp::IPv4Address netmask;

        PcapLiveDeviceWrapper(pcpp::PcapLiveDevice *device, pcpp::IPv4Address netmask);
    };

    inline pcpp::IPv4Address operator&(const pcpp::IPv4Address& a1, const pcpp::IPv4Address& a2) {
        return {a1.toInt() & a2.toInt()};
    }
}

#endif //PCAP_LIVE_DEVICE_WRAPPER_HPP
