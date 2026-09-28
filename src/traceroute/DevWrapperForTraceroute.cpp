#include "traceroute/DevWrapperForTraceroute.hpp"

netmap::DevWrapperForTraceroute::DevWrapperForTraceroute(pcpp::PcapLiveDevice *device,
                                                         const pcpp::MacAddress gateway_mac)
    : device(device), gateway_mac(gateway_mac) {
}
