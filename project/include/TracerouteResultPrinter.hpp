#ifndef TRACEROUTE_RESULT_PRINTER_HPP
#define TRACEROUTE_RESULT_PRINTER_HPP
#include <IpAddress.h>
#include <array>

#include "ResultPrinter.hpp"
#include "NetworkConstants.hpp"

namespace netmap {
    class TracerouteResultPrinter final: public ResultPrinter {
    private:
        const std::array<pcpp::IPv4Address, MAX_HOPS>& hops_;
        bool dest_hit_;
        pcpp::IPv4Address dest_ip_;
    protected:
        [[nodiscard]] inline std::string GetTitle() const override;
        void PrintHeader(std::stringstream& ss) const override;
        void PrintBody(std::stringstream& ss) const override;
    public:
        TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, pcpp::IPv4Address dest_ip, Logger& logger, PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string TracerouteResultPrinter::GetTitle() const {
        return " Traceroute Results";
    }
}

#endif //TRACEROUTE_RESULT_PRINTER_HPP