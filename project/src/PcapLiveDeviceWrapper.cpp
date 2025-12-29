#include "PcapLiveDeviceWrapper.hpp"

netmap::PcapLiveDeviceWrapper::PcapLiveDeviceWrapper(pcpp::PcapLiveDevice *device, pcpp::IPv4Address netmask)
    : device(device), netmask(netmask) {}

