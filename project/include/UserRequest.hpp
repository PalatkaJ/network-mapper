#ifndef USER_REQUEST_HPP
#define USER_REQUEST_HPP
#include <string>
#include "cxxopts.hpp"

namespace netmap {
    struct UserRequest {
        std::string interface_name;
        std::string traceroute_destination; // either concrete IP or domain name, which will get resolved to IP
        std::string output_filename;
        uint32_t timeout_ms = 5000;
        /*
        uint16_t port = 0;
        */
        bool verbose = false;
        bool help = false;

        void Initialize(const cxxopts::ParseResult &result);
        [[nodiscard]] bool isValid() const;
    };
}

#endif //USER_REQUEST_HPP
