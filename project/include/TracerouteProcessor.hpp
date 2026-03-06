#ifndef NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP
#define NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP
#include <IpAddress.h>

#include "RequestProcessor.hpp"

namespace netmap {
    class TracerouteProcessor: public RequestProcessor {
        const UserRequest &user_request_;
        Logger& logger_;

        pcpp::IPAddress ExtractIpAddress(const UserRequest &user_request);
        pcpp::IPAddress ResolveIp(const std::string &domain_name);

    public:
        explicit TracerouteProcessor(const UserRequest &user_request, Logger& logger);
        void Process() override;
    };
}

#endif //NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP