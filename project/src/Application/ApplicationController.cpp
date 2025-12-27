#include "ApplicationController.hpp"
#include "cxxopts.hpp"

#include "../RequestProcessors/RequestProcessor.hpp"
#include "../RequestProcessors/NetworkScanner.hpp"
#include "ScanRequest.hpp"

std::unique_ptr<netmap::RequestProcessor>
netmap::ApplicationController::GetRequestedProcessor(const cxxopts::Options &options, const cxxopts::ParseResult &result) {

    ScanRequest request;
    if (result.count("help") != 0) {
        return std::make_unique<HelpProvider>(options.help());
    }

    if (result.count("interface") != 0) {
        request.interface_name = result["interface"].as<std::string>();
    }

    // here we can expand to more options and change the request accordingly

    if (!request.isValid()) {
        throw cxxopts::exceptions::specification("Invalid arguments");
    }

    return std::make_unique<NetworkScanner>(std::move(request));
}

void netmap::ApplicationController::Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) {
    const auto request_processor = GetRequestedProcessor(options, result);

    request_processor->Process();
}
