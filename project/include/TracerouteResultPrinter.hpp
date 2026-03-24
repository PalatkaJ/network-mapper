#ifndef NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP
#define NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP
#include <IpAddress.h>
#include <array>

#include "ResultPrinter.hpp"
#include "NetworkConstants.hpp"

namespace netmap {
    class TracerouteResultPrinter final: public ResultPrinter {
    private:
        const std::array<pcpp::IPv4Address, MAX_HOPS>& hops_;
        bool dest_hit_;
    protected:
        [[nodiscard]] inline std::string GetTitle() const override;
        void PrintHeader(std::stringstream& ss) const override;
        void PrintBody(std::stringstream& ss) const override;
    public:
        TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, Logger& logger, PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string TracerouteResultPrinter::GetTitle() const {
        return " Traceroute Results";
    }
}

#endif //NETWORK_MAPPER_TRACEROUTERESULTPRINTER_HPP