#ifndef TRACEROUTE_RESULT_HPP
#define TRACEROUTE_RESULT_HPP
#include <array>
#include <IpAddress.h>

#include "NetworkConstants.hpp"

namespace netmap {
    struct TracerouteResult {
        const std::array<pcpp::IPv4Address, MAX_HOPS> hops;
        const pcpp::IPv4Address dest_ip;
        const bool destination_reached;
    };
}

#endif //TRACEROUTE_RESULT_HPP