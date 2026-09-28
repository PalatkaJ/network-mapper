#ifndef USER_REQUEST_HPP
#define USER_REQUEST_HPP

#include "app/NetworkConstants.hpp"

#include <string>
#include "cxxopts.hpp"


namespace netmap {
    /**
     * @brief Represents the user's command-line input and application configuration.
     *
     * This struct holds all the options specified by the user, such as the network
     * interface, the target for a traceroute, output file, and verbosity settings.
     */
    struct UserRequest {
        /** @brief The name of the network interface to use (e.g., "eth0"). */
        std::string interface_name;
        /** @brief The destination for a traceroute (IP address or domain name). */
        std::string traceroute_destination;
        /** @brief The path to the output file for saving results. */
        std::string output_filename;
        /** @brief Timeout in milliseconds for network operations. */
        uint32_t timeout_ms = DEFAULT_TIMEOUT_MS;

        /** @brief Flag to enable verbose logging. */
        bool verbose = false;
        /** @brief Flag indicating if the help message was requested. */
        bool help = false;

        /**
         * @brief Initializes the struct's members from parsed command-line options.
         * @param result The parsed options from cxxopts.
         */
        void Initialize(const cxxopts::ParseResult &result);

        /**
         * @brief Validates the user request to ensure it is coherent.
         * @return True if the request is valid, false otherwise.
         */
        [[nodiscard]] bool isValid() const;
    };
}

#endif //USER_REQUEST_HPP
