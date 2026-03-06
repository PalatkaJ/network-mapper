#ifndef NETWORK_MAPPER_ROUTE_TRACER_HPP
#define NETWORK_MAPPER_ROUTE_TRACER_HPP
#include <IpAddress.h>

#include "Logger.hpp"
#include "UserRequest.hpp"

namespace netmap {
    class RouteTracer {
        pcpp::IPAddress dest_ip_;
        Logger& logger_;

    public:
        RouteTracer(pcpp::IPAddress dest_ip, Logger& logger);
        void Execute();
    };
}

#endif //NETWORK_MAPPER_ROUTE_TRACER_HPP