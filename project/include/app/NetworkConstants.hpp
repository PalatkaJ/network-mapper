#ifndef NETWORK_CONSTANTS_HPP
#define NETWORK_CONSTANTS_HPP

#include <cstddef>

/**
 * @file
 * @brief Defines constants related to network operations and protocols.
 */

constexpr size_t MAX_HOPS = 128;
constexpr size_t ICMP_PACKET_SEND_GAP_MS = 5;
constexpr size_t DEFAULT_TIMEOUT_MS = 5000;

#endif //NETWORK_CONSTANTS_HPP
