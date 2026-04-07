#include "app/UserRequest.hpp"

#include <iostream>

void netmap::UserRequest::Initialize(const cxxopts::ParseResult &result) {
    if (result.count("help") != 0) {
        help = true;
    }

    if (result.count("verbose") != 0) {
        verbose = true;
    }

    if (result.count("interface") != 0) {
        interface_name = result["interface"].as<std::string>();
    }

    if (result.count("output") != 0) {
        output_filename = result["output"].as<std::string>();
    }

    if (result.count("timeout") != 0) {
        timeout_ms = result["timeout"].as<uint32_t>();
    }

    if (result.count("destination") != 0) {
        traceroute_destination = result["destination"].as<std::string>();
    }
}

bool netmap::UserRequest::isValid() const {
    bool some_spec = !std::empty(interface_name) || !std::empty(traceroute_destination);
    bool more_spec = !std::empty(interface_name) && !std::empty(traceroute_destination);

    return some_spec && !more_spec;
}