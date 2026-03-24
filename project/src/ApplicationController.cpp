#include "ApplicationController.hpp"
#include "cxxopts.hpp"
#include "InterfaceScanningProcessor.hpp"
#include "InvalidRequestProcessor.hpp"
#include "LoggerFactory.hpp"
#include "UserRequest.hpp"
#include "RequestProcessorFactory.hpp"

void ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) const {
    netmap::UserRequest user_request;
    user_request.Validate(result);

    const auto logger = netmap::LoggerFactory::CreateLogger(user_request);

    const auto request_processor = netmap::RequestProcessorFactory::CreateRequestProcessor(user_request, options, *logger);

    try {
        request_processor->Process();
    } catch (const std::exception &e) {
        auto processor = netmap::InvalidRequestProcessor{*logger_};
        processor.Process();
    }
}
