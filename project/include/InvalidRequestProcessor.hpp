
#ifndef INVALID_REQUEST_PROCESSOR_HPP
#define INVALID_REQUEST_PROCESSOR_HPP

#include "Logger.hpp"
#include "RequestProcessor.hpp"

namespace netmap {
    class InvalidRequestProcessor final: public RequestProcessor {
    public:
        explicit InvalidRequestProcessor(Logger& logger);
        void Process() override;
    };
}

#endif //INVALID_REQUEST_PROCESSOR_HPP