#ifndef LOGGER_FACTORY_HPP
#define LOGGER_FACTORY_HPP
#include <memory>

#include "Logger.hpp"

namespace netmap {
    class LoggerFactory {
    public:
        static std::unique_ptr<Logger> CreateLogger(const UserRequest &request);
    };
}

#endif //LOGGER_FACTORY_HPP