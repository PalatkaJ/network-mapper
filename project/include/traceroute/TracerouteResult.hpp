#ifndef TRACEROUTE_RESULT_HPP
#define TRACEROUTE_RESULT_HPP

#include "app/NetworkConstants.hpp"

#include <array>
#include <IpAddress.h>

namespace netmap {
    /**
     * @brief Holds the results of a traceroute operation.
     *
     * This is a data structure containing the list of discovered hops on the route
     * to a destination, the destination IP itself, and a flag indicating if the
     * destination was successfully reached.
     */
    struct TracerouteResult {
        /** @brief An array storing the IP address of each hop in the route. */
        const std::array<pcpp::IPv4Address, MAX_HOPS> hops;
        /** @brief The final destination IP address that was traced. */
        const pcpp::IPv4Address dest_ip;
        /** @brief A flag indicating whether the destination host was reached. */
        const bool destination_reached;
    };
}

#endif //TRACEROUTE_RESULT_HPP
