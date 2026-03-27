#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"

/**
 * @brief Main controller for the network scanning application.
 *
 * This class is responsible for orchestrating the
 * overall application flow, such as initiating an ARP scan or a traceroute based on users input.
 */
class ApplicationController {
public:
    /**
     * @brief Executes the main application logic based on parsed command-line options.
     * @param options The cxxopts::Options object (used for help text).
     * @param result The parsed command-line arguments and options.
     */
    static void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) ;
};

#endif //APPLICATION_CONTROLLER_HPP
