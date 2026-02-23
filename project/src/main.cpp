#include <cxxopts.hpp>
#include <iostream>

#include "Application/ApplicationController.hpp"
#include "Application/ApplicationConstants.hpp"

int main(int argc, char *argv[]) {
    auto options = cxxopts::Options("network-mapper",
                                    "CL tool implementing subset of arp-scan functionality");

    options.add_options()
            ("interface", "Network interface name to sniff on", cxxopts::value<std::string>())
            ("help", "Print usage")
            ("verbose", "Print verbose messages")
            ("output", "Specify output file", cxxopts::value<std::string>())
            ("timeout", "Specify for how long should the scanner scan provided interface (milliseconds)",
                cxxopts::value<uint32_t>());

    try {
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
