#ifndef REQUEST_PROCESSOR_FACTORY_HPP
#define REQUEST_PROCESSOR_FACTORY_HPP
#include "RequestProcessor.hpp"
#include "UserRequest.hpp"

namespace netmap {
    class RequestProcessorFactory {
    public:
        static std::unique_ptr<RequestProcessor> CreateRequestProcessor(const UserRequest &user_request, const cxxopts::Options &options, Logger& logger);
    };
}

#endif //REQUEST_PROCESSOR_FACTORY_HPP