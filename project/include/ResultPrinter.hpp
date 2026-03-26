#ifndef RESULT_PRINTER_HPP
#define RESULT_PRINTER_HPP
#include "Logger.hpp"
#include "PrinterConfig.hpp"

namespace netmap {
    /**
     * @brief Abstract base class for printing formatted results.
     *
     * This class defines a common interface for various printer implementations
     * (e.g., for ARP scans, traceroute). It provides a template for generating
     * titled, headed, and bodied output.
     */
    class ResultPrinter {
    protected:
        Logger &logger_;
        PrinterConfig printer_config_;

        /**
         * @brief Gets the title for the output.
         * @return The title string.
         */
        [[nodiscard]] virtual std::string GetTitle() const = 0;

        /**
         * @brief Prints the header section of the output.
         * @param ss The string stream to write to.
         */
        virtual void PrintHeader(std::stringstream &ss) const = 0;

        /**
         * @brief Prints the main body of the output.
         * @param ss The string stream to write to.
         */
        virtual void PrintBody(std::stringstream &ss) const = 0;

    public:
        /**
         * @brief Constructs a ResultPrinter.
         * @param logger A logger instance.
         * @param printer_config Configuration for the printer.
         */
        ResultPrinter(Logger &logger, PrinterConfig printer_config);

        virtual ~ResultPrinter() = default;

        /**
         * @brief Prints the complete formatted result to the configured output.
         *
         * This method orchestrates the calls to GetTitle, PrintHeader, and PrintBody
         * to generate the full output.
         */
        virtual void Print() const;
    };
}

#endif //RESULT_PRINTER_HPP
