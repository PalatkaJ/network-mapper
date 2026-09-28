#ifndef TRACEROUTE_PROCESSOR_HPP
#define TRACEROUTE_PROCESSOR_HPP

#include "app/RequestProcessor.hpp"
#include "app/UserRequest.hpp"

#include <ifaddrs.h>
#include <IpAddress.h>

#include <string>


namespace netmap {
    /**
     * @brief A request processor for executing a traceroute operation.
     *
     * This class implements the RequestProcessor interface and encapsulates the
     * high-level logic for performing a traceroute, from resolving the destination
     * domain name to running the trace and printing the results.
     */
    class TracerouteProcessor final : public RequestProcessor {
        const UserRequest &user_request_;

        pcpp::IPv4Address ExtractDestIpAddress(const UserRequest &user_request);

        pcpp::IPv4Address DNSResolveIp(const std::string &domain_name);

        static bool IsTargetIfa(const ifaddrs *ifa);

        static pcpp::IPv4Address GetMyIp();

    public:
        /**
         * @brief Constructs a TracerouteProcessor.
         * @param user_request The user's configuration for the traceroute.
         * @param logger A logger instance for logging messages.
         */
        explicit TracerouteProcessor(const UserRequest &user_request, Logger &logger);

        /**
         * @brief Executes the traceroute process.
         *
         * This method handles DNS resolution, device lookup, executing the
         * traceroute logic, and printing the final results.
         */
        void Process() override;
    };
}

#endif //TRACEROUTE_PROCESSOR_HPP
