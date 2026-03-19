#ifndef NETWORK_MAPPER_ROUTE_TRACER_HPP
#define NETWORK_MAPPER_ROUTE_TRACER_HPP
#include <IpAddress.h>
#include <PcapLiveDevice.h>

#include "IcmpReplyHandler.hpp"
#include "Logger.hpp"
#include "UserRequest.hpp"

namespace netmap {
    class RouteTracer {
        pcpp::IPv4Address source_ip_;
        pcpp::IPv4Address dest_ip_;
        Logger& logger_;

    public:
        RouteTracer(pcpp::IPv4Address source_ip, pcpp::IPv4Address dest_ip, Logger& logger);

        void FindRoute(pcpp::PcapLiveDevice* dev, pcpp::MacAddress gateaway_mac);

        static void OnIcmpPacketCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie);

        IcmpReplyHandler Execute();
    };
}

#endif //NETWORK_MAPPER_ROUTE_TRACER_HPP