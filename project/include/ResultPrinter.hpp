#ifndef NETWORK_MAPPER_RESULTPRINTER_HPP
#define NETWORK_MAPPER_RESULTPRINTER_HPP
#include "Logger.hpp"
#include "PrinterConfig.hpp"

namespace netmap {
    class ResultPrinter {
    protected:
        Logger& logger_;
        PrinterConfig printer_config_;

        [[nodiscard]] virtual std::string GetTitle() const = 0;
        virtual void PrintHeader(std::stringstream & ss) const = 0;
        virtual void PrintBody(std::stringstream & ss) const = 0;
    public:
        ResultPrinter(Logger &logger, PrinterConfig &&printer_config);
        virtual ~ResultPrinter() = default;

        virtual void Print() const;
    };
}

#endif //NETWORK_MAPPER_RESULTPRINTER_HPP