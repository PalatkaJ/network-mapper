#include "RouteTracer.hpp"
#include <format>
#include <ifaddrs.h>

netmap::RouteTracer::RouteTracer(pcpp::IPAddress dest_ip, Logger &logger)
    : dest_ip_(dest_ip), logger_(logger){}

void netmap::RouteTracer::Execute() {
    logger_.VerboseLog(std::format("finding path (traceroute) for destination ip: {}", dest_ip_.getIPv4().toString()));

    // TODO
}
