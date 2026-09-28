#ifndef LOGGER_FACTORY_HPP
#define LOGGER_FACTORY_HPP

#include "Logger.hpp"
#include "UserRequest.hpp"

#include <memory>

namespace netmap {
    /**
     * @brief A factory for creating Logger instances.
     *
     * This class provides a static method to construct a configured Logger
     * based on the settings provided in a UserRequest object.
     */
    class LoggerFactory {
    public:
        /**
         * @brief Creates a Logger instance based on user request settings.
         *
         * This factory method will configure the logger's verbosity and output
         * stream (e.g., stdout or a file) based on the user's command-line options.
         * @param request The user request configuration.
         * @return A std::unique_ptr to the newly created Logger.
         */
        static std::unique_ptr<Logger> CreateLogger(const UserRequest &request);
    };
}

#endif //LOGGER_FACTORY_HPP
