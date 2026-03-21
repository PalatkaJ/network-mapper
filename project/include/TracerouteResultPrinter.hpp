#ifndef NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP
#define NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP
#include <IpAddress.h>
#include <array>

#include "ResultPrinter.hpp"
#include "NetworkConstants.hpp"

namespace netmap {
    class TracerouteResultPrinter: public ResultPrinter {
    private:
        const std::array<pcpp::IPv4Address, MAX_HOPS>& hops_;
        bool dest_hit_;
    public:
        TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, Logger& logger);
        void Print() const override;
    };
}

#endif //NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP