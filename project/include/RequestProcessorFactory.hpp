#ifndef NETWORK_MAPPER_REQUESTPROCESSORFACTORY_HPP
#define NETWORK_MAPPER_REQUESTPROCESSORFACTORY_HPP
#include "RequestProcessor.hpp"
#include "UserRequest.hpp"

namespace netmap {
    class RequestProcessorFactory {
    public:
        static std::unique_ptr<RequestProcessor> CreateRequestProcessor(const UserRequest &user_request, const cxxopts::Options &options, Logger& logger);
    };
}

#endif //NETWORK_MAPPER_REQUESTPROCESSORFACTORY_HPP