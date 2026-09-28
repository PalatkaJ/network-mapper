#ifndef ROUTE_TRACER_HPP
#define ROUTE_TRACER_HPP

#include "DevWrapperForTraceroute.hpp"
#include "TracerouteResult.hpp"
#include "app/UserRequest.hpp"
#include "app/Logger.hpp"

#include <IpAddress.h>
#include <PcapLiveDevice.h>

#include "RawPacket.h"

namespace netmap {
    /**
     * @brief Performs a traceroute to a destination host.
     *
     * This class discovers the network path (route) to a given destination IP address
     * by sending packets with incrementally increasing TTL (Time-To-Live) values.
     */
    class RouteTracer {
        pcpp::IPv4Address source_ip_;
        pcpp::IPv4Address dest_ip_;
        Logger &logger_;
        const UserRequest &user_request_;
        DevWrapperForTraceroute &dev_wrapper_;

        void FindRoute();

        static void OnIcmpPacketCapture(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *iface, void *cookie);

    public:
        /**
         * @brief Constructs a RouteTracer.
         * @param dev_wrapper A wrapper for the network device.
         * @param source_ip The source IPv4 address for outgoing packets.
         * @param dest_ip The destination IPv4 address to trace the route to.
         * @param logger A logger instance for logging messages.
         * @param user_request The user's request configuration.
         */
        RouteTracer(DevWrapperForTraceroute &dev_wrapper, pcpp::IPv4Address source_ip, pcpp::IPv4Address dest_ip,
                    Logger &logger, const UserRequest &user_request);

        /**
         * @brief Executes the traceroute operation.
         * @return A TracerouteResult object containing the hops and status of the trace.
         */
        TracerouteResult Execute();
    };
}

#endif //ROUTE_TRACER_HPP
