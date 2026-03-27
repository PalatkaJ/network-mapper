#ifndef TRACEROUTE_RESULT_PRINTER_HPP
#define TRACEROUTE_RESULT_PRINTER_HPP
#include <IpAddress.h>
#include <array>
#include <string>
#include <sstream>

#include "ResultPrinter.hpp"
#include "NetworkConstants.hpp"
#include "PrinterConfig.hpp"

namespace netmap {
    /**
     * @brief Formats and prints the results of a traceroute operation.
     *
     * This class inherits from ResultPrinter and is specialized for printing
     * the discovered route, including hop numbers and IP addresses, in a
     * human-readable format.
     */
    class TracerouteResultPrinter final : public ResultPrinter {
        const std::array<pcpp::IPv4Address, MAX_HOPS> &hops_;
        bool dest_hit_;
        pcpp::IPv4Address dest_ip_;

    protected:
        /**
         * @brief Gets the title for the results output.
         * @return The title string.
         */
        [[nodiscard]] inline std::string GetTitle() const override;

        /**
         * @brief Prints the header of the results table.
         * @param ss The string stream to write the output to.
         */
        void PrintHeader(std::stringstream &ss) const override;

        /**
         * @brief Prints the main body of the results table (the route).
         * @param ss The string stream to write the output to.
         */
        void PrintBody(std::stringstream &ss) const override;

    public:
        /**
         * @brief Constructs a TracerouteResultPrinter.
         * @param hops The array of discovered hop IP addresses.
         * @param dest_hit A flag indicating if the destination was reached.
         * @param dest_ip The final destination IP address.
         * @param logger A logger instance.
         * @param printer_config Configuration for the printer.
         */
        TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit,
                                pcpp::IPv4Address dest_ip, Logger &logger,
                                PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string TracerouteResultPrinter::GetTitle() const {
        return " Traceroute Results";
    }
}

#endif //TRACEROUTE_RESULT_PRINTER_HPP
