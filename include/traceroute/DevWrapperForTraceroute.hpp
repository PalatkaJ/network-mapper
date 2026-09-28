#ifndef DEV_WRAPPER_FOR_TRACEROUTE_HPP
#define DEV_WRAPPER_FOR_TRACEROUTE_HPP
#include <PcapLiveDevice.h>
#include <MacAddress.h>

namespace netmap {
    /**
     * @brief Wraps a network device and gateway MAC address for traceroute.
     *
     * This struct bundles a pointer to a live PcapPlusPlus device with the MAC
     * address of the default gateway, which is needed to send packets off the
     * local network segment.
     */
    struct DevWrapperForTraceroute {
        /** @brief A pointer to the live network capture device. */
        pcpp::PcapLiveDevice *device;
        /** @brief The MAC address of the default gateway. */
        const pcpp::MacAddress gateway_mac;

        /**
         * @brief Constructs a DevWrapperForTraceroute.
         * @param device A pointer to the live device.
         * @param gateway_mac The MAC address of the gateway.
         */
        DevWrapperForTraceroute(pcpp::PcapLiveDevice *device, const pcpp::MacAddress gateway_mac);
    };
}

#endif //DEV_WRAPPER_FOR_TRACEROUTE_HPP
