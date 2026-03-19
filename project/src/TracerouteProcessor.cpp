#include "TracerouteProcessor.hpp"

#include <ifaddrs.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <IpAddress.h>
#include <arpa/inet.h>
#include <net/if.h>

#include "RouteTracer.hpp"

pcpp::IPv4Address netmap::TracerouteProcessor::ExtractDestIpAddress(const UserRequest &user_request) {
    pcpp::IPv4Address ip;

    try {
        ip = pcpp::IPv4Address{user_request.traceroute_destination};
    } catch (const std::invalid_argument& e) {
        ip = DNSResolveIp(user_request.traceroute_destination);
    }

    return ip;
}

pcpp::IPv4Address netmap::TracerouteProcessor::DNSResolveIp(const std::string &domain_name) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domain_name.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        throw std::invalid_argument(std::format("DNS resolution failed for {}: {}",
                                    domain_name, gai_strerror(status)));
    }

    auto* ipv4_addr = reinterpret_cast<sockaddr_in*>(res->ai_addr);

    pcpp::IPv4Address res_ip(ipv4_addr->sin_addr.s_addr);

    logger_.VerboseLog(std::format("Extracted host addr: {}", res_ip.toString()));

    freeaddrinfo(res);
    return res_ip;
}

bool netmap::TracerouteProcessor::IsTargetIfa(const ifaddrs *ifa) {
    return ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && !(ifa->ifa_flags & IFF_LOOPBACK);
}


pcpp::IPv4Address netmap::TracerouteProcessor::GetMyIp() {
    ifaddrs *ifap = nullptr;

    if (getifaddrs(&ifap) != 0) {
        throw std::runtime_error("parsing network interfaces on machine failed");
    }

    for (const ifaddrs *ifa = ifap; ifa != nullptr; ifa = ifa->ifa_next) {
        if (IsTargetIfa(ifa)) {
            char my_ip[INET_ADDRSTRLEN];

            inet_ntop(AF_INET, &reinterpret_cast<sockaddr_in *>(ifa->ifa_addr)->sin_addr,
                    my_ip, INET_ADDRSTRLEN);

            freeifaddrs(ifap);
            return {my_ip};
        }
    }

    freeifaddrs(ifap);

    throw std::runtime_error("could not find proper network interface");
}

netmap::TracerouteProcessor::TracerouteProcessor(const UserRequest &user_request, Logger &logger)
    : user_request_(user_request),logger_(logger){}


void netmap::TracerouteProcessor::Process() {
    auto dest_ip = ExtractDestIpAddress(user_request_);
    auto my_ip = GetMyIp();

    auto route_tracer = RouteTracer{my_ip, dest_ip, logger_};
    auto stats = route_tracer.Execute();

    for (auto ip: stats.GetHitIps()) {
        logger_.VerboseLog(ip.toString());
    }

    if (stats.IsDestHit()) {
        logger_.VerboseLog(std::format("Destination reached after {} hops", stats.GetHitIps().size() + 1));
    }
}
