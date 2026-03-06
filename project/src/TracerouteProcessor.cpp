#include "TracerouteProcessor.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <IpAddress.h>

#include "RouteTracer.hpp"

pcpp::IPAddress netmap::TracerouteProcessor::ExtractIpAddress(const UserRequest &user_request) {
    pcpp::IPAddress ip;

    try {
        ip = pcpp::IPAddress{user_request.traceroute_destination};
    } catch (const std::invalid_argument& e) {
        ip = ResolveIp(user_request.traceroute_destination);
    }

    return ip;
}

pcpp::IPAddress netmap::TracerouteProcessor::ResolveIp(const std::string &domain_name) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domain_name.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        throw std::invalid_argument(std::format("DNS resolution failed for {}: {}",
                                    domain_name, gai_strerror(status)));
    }

    auto* ipv4_addr = reinterpret_cast<sockaddr_in*>(res->ai_addr);

    pcpp::IPAddress res_ip(ipv4_addr->sin_addr.s_addr);

    logger_.VerboseLog(std::format("Extracted host addr: {}", res_ip.toString()));

    freeaddrinfo(res);
    return res_ip;
}

netmap::TracerouteProcessor::TracerouteProcessor(const UserRequest &user_request, Logger &logger)
    : user_request_(user_request),logger_(logger){}


void netmap::TracerouteProcessor::Process() {
    auto ip = ExtractIpAddress(user_request_);

    auto route_tracer = RouteTracer{ip, logger_};
    route_tracer.Execute();
}
