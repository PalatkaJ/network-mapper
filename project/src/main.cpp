#include <cxxopts.hpp>
#include <iostream>
#include <unistd.h>

#include "ApplicationController.hpp"
#include "ApplicationConstants.hpp"

void check_root_privileges() {
    if (geteuid() != 0) {
        throw std::runtime_error("This program must be run with root privileges (sudo). "
                                 "Required for raw socket access (ARP/Sniffing).");
    }
}

int main(int argc, char *argv[]) {
    auto options = cxxopts::Options("network-mapper",
                                    "CL tool implementing subset of arp-scan and traceroute functionality");

    options.add_options()
            ("i,interface", "Network interface name to sniff on", cxxopts::value<std::string>())
            ("h,help", "Print usage")
            ("v,verbose", "Print verbose messages")
            ("o,output", "Specify output file", cxxopts::value<std::string>())
            ("t, timeout", "Specify for how long should the scanner scan provided interface (milliseconds)",
             cxxopts::value<uint32_t>())
            ("d, destination", "Trace the route to the provided destination (IP address or domain name).",
             cxxopts::value<std::string>());

    try {
        check_root_privileges();
        const cxxopts::ParseResult result = options.parse(argc, argv);
        ApplicationController::Run(options, result);
    } catch (const cxxopts::exceptions::specification &se) {
        std::cerr << "Error in option specification: " << se.what() << std::endl << options.help() << std::endl;
        return RUNTIME_ERROR_CODE;
    } catch (const cxxopts::exceptions::parsing &pe) {
        std::cerr << "Error parsing options: " << pe.what() << std::endl << options.help() << std::endl;
        return RUNTIME_ERROR_CODE;
    } catch (const std::runtime_error &re) {
        std::cerr << "Error: " << re.what() << std::endl;
        return RUNTIME_ERROR_CODE;
    }

    return 0;
}