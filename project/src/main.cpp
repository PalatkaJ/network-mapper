#include <cxxopts.hpp>
#include <iostream>

#include "ApplicationController.hpp"
#include "ApplicationConstants.hpp"

int main(int argc, char *argv[]) {
    auto options = cxxopts::Options("network-mapper",
                                    "CL tool implementing subset of arp-scan functionality");

    options.add_options()
            ("i,interface", "Network interface name to sniff on", cxxopts::value<std::string>())
            ("h,help", "Print usage")
            ("v,verbose", "Print verbose messages")
            ("o,output", "Specify output file", cxxopts::value<std::string>())
            ("t,timeout", "Specify for how long should the scanner scan provided interface (milliseconds)",
                cxxopts::value<uint32_t>())
            ("r,route", "Traceroute provided ip address or domain name (e.g. 8.8.8.8 or google.com)", cxxopts::value<std::string>());

    try {
        // TODO refactor this, so the steps are:
        // rename ScanRequest to ArgOptions, initialize them
        // then initialize the logger if everything is fine with ArgOptions
        // then get the requested processor based on the ArgOptions
        // then process the request ...
        const cxxopts::ParseResult result = options.parse(argc, argv);
        ApplicationController application_controller;
        application_controller.Run(options, result);
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
