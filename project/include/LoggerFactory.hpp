#ifndef NETWORK_MAPPER_LOGGERFACTORY_HPP
#define NETWORK_MAPPER_LOGGERFACTORY_HPP
#include <memory>

#include "Logger.hpp"

namespace netmap {
    class LoggerFactory {
    public:
        static std::unique_ptr<Logger> CreateLogger(const UserRequest &request);
    };
}

#endif //NETWORK_MAPPER_LOGGERFACTORY_HPP