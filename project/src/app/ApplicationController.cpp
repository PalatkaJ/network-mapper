#include "app/ApplicationController.hpp"
#include "arp-scan/ArpScanProcessor.hpp"
#include "app/InvalidRequestProcessor.hpp"
#include "app/LoggerFactory.hpp"
#include "app/UserRequest.hpp"
#include "app/RequestProcessorFactory.hpp"

#include <iostream>

#include "cxxopts.hpp"

void ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    netmap::UserRequest user_request;
    user_request.Initialize(result);

    const auto logger = netmap::LoggerFactory::CreateLogger(user_request);

    const auto request_processor = netmap::RequestProcessorFactory::CreateRequestProcessor(
        user_request, options, *logger);

    request_processor->Process();
    /*
    try {
    } catch (const std::exception &e) {
        auto processor = netmap::InvalidRequestProcessor{*logger};
        processor.Process();
    }
    */
}
