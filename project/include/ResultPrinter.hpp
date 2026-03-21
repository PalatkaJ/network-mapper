#ifndef NETWORK_MAPPER_RESULTPRINTER_HPP
#define NETWORK_MAPPER_RESULTPRINTER_HPP
#include "Logger.hpp"

namespace netmap {
    class ResultPrinter {
    protected:
        Logger& logger_;
    public:
        explicit ResultPrinter(Logger& logger);
        virtual ~ResultPrinter() = default;
        virtual void Print() const = 0;
    };
}

#endif //NETWORK_MAPPER_RESULTPRINTER_HPP