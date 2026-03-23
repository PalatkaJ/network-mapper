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
        void PrintHeader(std::stringstream& ss, size_t width, char main_sep, char sub_sep) const;
        void PrintBody(std::stringstream& ss, size_t width, char sub_sep) const;
    };
}

#endif //NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP