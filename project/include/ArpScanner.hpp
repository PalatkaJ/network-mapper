#ifndef ARPSCANNER_HPP
#define ARPSCANNER_HPP
#include <iostream>

#include "PcapLiveDeviceWrapper.hpp"


namespace netmap {
    class ArpScanner {
    private:
        PcapLiveDeviceWrapper& wrappedDev_;

        pcpp::IPv4Address GetStartingIpAddress() const;
        static void IncrementIpAddress(pcpp::IPv4Address& ip);
        void ProcessIp(const pcpp::IPv4Address& ip) const;
        static uint32_t GetHostIntFromNetIp(const pcpp::IPv4Address& ip);

    public:
        explicit ArpScanner(PcapLiveDeviceWrapper& wrappedDev);

        void Process() const;
    };
}


#endif //ARPSCANNER_HPP
