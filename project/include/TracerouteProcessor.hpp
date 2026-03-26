#ifndef TRACEROUTE_PROCESSOR_HPP
#define TRACEROUTE_PROCESSOR_HPP
#include <ifaddrs.h>
#include <IpAddress.h>

#include "RequestProcessor.hpp"

namespace netmap {
    class TracerouteProcessor final: public RequestProcessor {
        const UserRequest &user_request_;

        pcpp::IPv4Address ExtractDestIpAddress(const UserRequest &user_request);
        pcpp::IPv4Address DNSResolveIp(const std::string &domain_name);

        static bool IsTargetIfa(const ifaddrs * ifa);

        static pcpp::IPv4Address GetMyIp();

    public:
        explicit TracerouteProcessor(const UserRequest &user_request, Logger& logger);
        void Process() override;
    };
}

#endif //TRACEROUTE_PROCESSOR_HPP