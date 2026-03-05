#ifndef NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP
#define NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP
#include "RequestProcessor.hpp"

namespace netmap {
    class TracerouteProcessor: public RequestProcessor {
        Logger& logger_;
    public:
        explicit TracerouteProcessor(Logger& logger);
        void Process() override;
    };
}

#endif //NETWORK_MAPPER_TRACEROUTE_PROCESSOR_HPP