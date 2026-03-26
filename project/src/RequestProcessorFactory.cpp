#include "RequestProcessorFactory.hpp"

#include "ArpScanProcessor.hpp"
#include "TracerouteProcessor.hpp"
#include "InvalidRequestProcessor.hpp"

std::unique_ptr<netmap::RequestProcessor>
netmap::RequestProcessorFactory::CreateRequestProcessor(const UserRequest &user_request, const cxxopts::Options &options, Logger& logger) {
    if (user_request.help) {
        return std::make_unique<HelpProcessor>(options.help(), logger);
    }

    if (!user_request.isValid()) {
        return std::make_unique<InvalidRequestProcessor>(logger);
    }

    if (!std::empty(user_request.interface_name)) {
        return std::make_unique<ArpScanProcessor>(user_request, logger);
    }

    return std::make_unique<TracerouteProcessor>(user_request, logger);
}
