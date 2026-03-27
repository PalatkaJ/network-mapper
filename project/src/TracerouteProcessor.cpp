#include "TracerouteProcessor.hpp"

#include <ifaddrs.h>
#include <sys/socket.h>
#include <netdb.h>
#include <IpAddress.h>
#include <NetworkUtils.h>
#include <PcapLiveDeviceList.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <format>

#include "DevWrapperForTraceroute.hpp"
#include "RouteTracer.hpp"
#include "TracerouteResultPrinter.hpp"

pcpp::IPv4Address netmap::TracerouteProcessor::ExtractDestIpAddress(const UserRequest &user_request) {
    pcpp::IPv4Address ip;

    try {
        ip = pcpp::IPv4Address{user_request.traceroute_destination};
    } catch (const std::invalid_argument &e) {
        ip = DNSResolveIp(user_request.traceroute_destination);
    }

    return ip;
}

pcpp::IPv4Address netmap::TracerouteProcessor::DNSResolveIp(const std::string &domain_name) {
    logger_.VerboseLog(std::format("Resolving IP for domain name: {}", domain_name));

    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    int status = getaddrinfo(domain_name.c_str(), nullptr, &hints, &res);
    if (status != 0) {
        throw std::invalid_argument(std::format("DNS resolution failed for {}: {}",
                                                domain_name, gai_strerror(status)));
    }

    auto *ipv4_addr = reinterpret_cast<sockaddr_in *>(res->ai_addr);

    pcpp::IPv4Address res_ip(ipv4_addr->sin_addr.s_addr);

    freeaddrinfo(res);
    return res_ip;
}

bool netmap::TracerouteProcessor::IsTargetIfa(const ifaddrs *ifa) {
    return ifa->ifa_addr && ifa->ifa_addr->sa_family == AF_INET && !(ifa->ifa_flags & IFF_LOOPBACK);
}


pcpp::IPv4Address netmap::TracerouteProcessor::GetMyIp() {
    ifaddrs *ifap = nullptr;

    if (getifaddrs(&ifap) != 0) {
        throw std::runtime_error("Parsing network interfaces on machine failed");
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

    throw std::runtime_error("Could not find proper network interface");
}

netmap::TracerouteProcessor::TracerouteProcessor(const UserRequest &user_request, Logger &logger)
    : RequestProcessor(logger), user_request_(user_request) {
}


void netmap::TracerouteProcessor::Process() {
    auto dest_ip = ExtractDestIpAddress(user_request_);
    logger_.VerboseLog(std::format("Extracted destination IP addr: {}", dest_ip.toString()));
    auto my_ip = GetMyIp();
    logger_.VerboseLog(std::format("Source IP used: {}", my_ip.toString()));

    auto *dev = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(my_ip);

    if (dev == nullptr) {
        throw std::runtime_error{std::format("Could not find proper network interface to use")};
    }

    logger_.VerboseLog(std::format("Interface that will be used: {}", dev->getName()));


    auto net_utils = pcpp::NetworkUtils::getInstance();
    double arp_response_time = 1000.0;

    auto gateway_mac = net_utils.getMacAddress(dev->getDefaultGateway(), dev, arp_response_time, dev->getMacAddress(),
                                               my_ip);
    logger_.VerboseLog(std::format("Resolved gateway mac to: {}", gateway_mac.toString()));
    auto dev_wrapper = DevWrapperForTraceroute{dev, gateway_mac};

    auto route_tracer = RouteTracer{dev_wrapper, my_ip, dest_ip, logger_, user_request_};
    auto result = route_tracer.Execute();
    logger_.VerboseLog("Traceroute finished");

    auto traceroute_printer = TracerouteResultPrinter{result.hops, result.destination_reached, result.dest_ip, logger_};
    traceroute_printer.Print();
}