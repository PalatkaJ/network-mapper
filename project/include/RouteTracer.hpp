#ifndef ROUTE_TRACER_HPP
#define ROUTE_TRACER_HPP
#include <IpAddress.h>
#include <PcapLiveDevice.h>

#include "DevWrapperForTraceroute.hpp"
#include "IcmpReplyHandler.hpp"
#include "Logger.hpp"
#include "NetworkConstants.hpp"
#include "TracerouteResult.hpp"

namespace netmap {
    class RouteTracer {
        pcpp::IPv4Address source_ip_;
        pcpp::IPv4Address dest_ip_;
        Logger& logger_;
        const UserRequest& user_request_;
        DevWrapperForTraceroute& dev_wrapper_;

        void FindRoute();
        static void OnIcmpPacketCapture(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *iface, void *cookie);

    public:
        RouteTracer(DevWrapperForTraceroute& dev_wrapper, pcpp::IPv4Address source_ip, pcpp::IPv4Address dest_ip, Logger& logger, const UserRequest &user_request);

        TracerouteResult Execute();
    };
}

#endif //ROUTE_TRACER_HPP