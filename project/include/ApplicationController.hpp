#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"
#include "RequestProcessor.hpp"
#include "Logger.hpp"

class ApplicationController {
    std::unique_ptr<Logger> logger_;

    void InitializeLogger(const ScanRequest &request);

public:
    std::unique_ptr<netmap::RequestProcessor> GetRequestedProcessor(const cxxopts::Options &options,
                                                           const cxxopts::ParseResult &result);

    void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result);
};

#endif //APPLICATION_CONTROLLER_HPP
