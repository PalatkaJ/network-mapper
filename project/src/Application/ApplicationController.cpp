#include "Application/ApplicationController.hpp"

#include <fstream>
#include <iostream>

#include "cxxopts.hpp"

#include "RequestProcessor.hpp"
#include "InterfaceScanningProcessor.hpp"
#include "ScanRequest.hpp"

std::unique_ptr<netmap::RequestProcessor>
ApplicationController::GetRequestedProcessor(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    ScanRequest request;

    if (result.count("help") != 0) {
        return std::make_unique<netmap::HelpProvider>(options.help());
    }

    if (result.count("verbose") != 0) {
        request.verbose = true;
    }

    if (result.count("interface") != 0) {
        request.interface_name = result["interface"].as<std::string>();
    }

    if (result.count("output") != 0) {
        request.output_filename = result["output"].as<std::string>();
    }

    if (result.count("timeout") != 0) {
        request.timeout_ms = result["timeout"].as<uint32_t>();
    }

    // here we can expand to more options and change the request accordingly

    if (!request.isValid()) {
        throw cxxopts::exceptions::specification("Invalid arguments");
    }

    InitializeLogger(request);

    return std::make_unique<netmap::InterfaceScanningProcessor>(std::move(request), *logger_);
}

void ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    const auto request_processor = GetRequestedProcessor(options, result);

    request_processor->Process();
}

void ApplicationController::InitializeLogger(const ScanRequest &request) {
    std::unique_ptr<std::ofstream> file_stream = nullptr;

    if (!request.output_filename.empty()) {
        file_stream = std::make_unique<std::ofstream>(request.output_filename);
        if (!file_stream->is_open()) {
            throw std::runtime_error("Could not open output file");
        }
    }

    logger_ = std::make_unique<Logger>(request.verbose, std::move(file_stream));
}

