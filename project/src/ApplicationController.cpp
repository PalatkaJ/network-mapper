#include "ApplicationController.hpp"
#include "cxxopts.hpp"
#include "ArpScanProcessor.hpp"
#include "InvalidRequestProcessor.hpp"
#include "LoggerFactory.hpp"
#include "UserRequest.hpp"
#include "RequestProcessorFactory.hpp"

void ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    netmap::UserRequest user_request;
    user_request.Initialize(result);

    const auto logger = netmap::LoggerFactory::CreateLogger(user_request);

    const auto request_processor = netmap::RequestProcessorFactory::CreateRequestProcessor(
        user_request, options, *logger);

    try {
        request_processor->Process();
    } catch (const std::exception &e) {
        auto processor = netmap::InvalidRequestProcessor{*logger};
        processor.Process();
    }
}
