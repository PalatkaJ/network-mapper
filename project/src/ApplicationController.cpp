#include "ApplicationController.hpp"

#include <fstream>
#include <iostream>
#include <ranges>

#include "cxxopts.hpp"

#include "RequestProcessor.hpp"
#include "InterfaceScanningProcessor.hpp"
#include "InvalidRequestProcessor.hpp"
#include "TracerouteProcessor.hpp"
#include "UserRequest.hpp"

std::unique_ptr<netmap::RequestProcessor>
ApplicationController::GetRequestedProcessor(const netmap::UserRequest &user_request, const cxxopts::Options &options) const {
    if (user_request.help) {
        return std::make_unique<netmap::HelpProcessor>(options.help());
    }

    if (!user_request.isValid()) {
        return std::make_unique<netmap::InvalidRequestProcessor>(*logger_);
    }

    if (!std::empty(user_request.interface_name)) {
        return std::make_unique<netmap::InterfaceScanningProcessor>(user_request, *logger_);
    }

    return std::make_unique<netmap::TracerouteProcessor>(*logger_);
}

void ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    std::unique_ptr<netmap::UserRequest> user_request_ptr = ParseUserRequest(result);
    InitializeLogger(*user_request_ptr);

    const auto request_processor = GetRequestedProcessor(*user_request_ptr, options);

    request_processor->Process();
}

void ApplicationController::InitializeLogger(const netmap::UserRequest &request) {
    std::unique_ptr<std::ofstream> file_stream = nullptr;

    if (!request.output_filename.empty()) {
        file_stream = std::make_unique<std::ofstream>(request.output_filename);
        if (!file_stream->is_open()) {
            throw std::runtime_error("Could not open output file");
        }
    }

    logger_ = std::make_unique<Logger>(request.verbose, std::move(file_stream));
}

std::unique_ptr<netmap::UserRequest> ApplicationController::ParseUserRequest(const cxxopts::ParseResult &result) {
    auto request = std::make_unique<netmap::UserRequest>();

    if (result.count("help") != 0) {
        request->help = true;
    }

    if (result.count("verbose") != 0) {
        request->verbose = true;
    }

    if (result.count("interface") != 0) {
        request->interface_name = result["interface"].as<std::string>();
    }

    if (result.count("output") != 0) {
        request->output_filename = result["output"].as<std::string>();
    }

    if (result.count("timeout") != 0) {
        request->timeout_ms = result["timeout"].as<uint32_t>();
    }

    if (result.count("traceroute") != 0) {
        request->traceroute_destination = result["traceroute"].as<std::string>();
    }

    return request;
}

