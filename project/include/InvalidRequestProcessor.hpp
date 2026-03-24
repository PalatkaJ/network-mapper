
#ifndef NETWORK_MAPPER_INVALID_REQUEST_PROCESSOR_HPP
#define NETWORK_MAPPER_INVALID_REQUEST_PROCESSOR_HPP

#include "Logger.hpp"
#include "RequestProcessor.hpp"

namespace netmap {
    class InvalidRequestProcessor final: public RequestProcessor {
        Logger& logger_;
    public:
        explicit InvalidRequestProcessor(Logger& logger);
        void Process() override;
    };
}

#endif //NETWORK_MAPPER_INVALID_REQUEST_PROCESSOR_HPP