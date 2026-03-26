#ifndef REQUEST_PROCESSOR_HPP
#define REQUEST_PROCESSOR_HPP
#include "cxxopts.hpp"
#include "Logger.hpp"

namespace netmap {
    /**
     * @brief Abstract base class for processing a user request.
     *
     * This class defines the interface for different types of request processors,
     * allowing for different actions (like scanning, tracing, or showing help)
     * to be executed polymorphically.
     */
    class RequestProcessor {
    protected:
        Logger &logger_;

    public:
        /**
         * @brief Constructs a RequestProcessor.
         * @param logger A logger instance for logging messages.
         */
        explicit RequestProcessor(Logger &logger);

        virtual ~RequestProcessor() = default;

        /**
         * @brief Pure virtual method to be implemented by derived classes.
         *
         * This method contains the logic for processing a specific type of request.
         */
        virtual void Process() = 0;
    };

    /**
     * @brief A concrete processor for displaying the help message.
     */
    class HelpProcessor final : public RequestProcessor {
        std::string_view help_;

    public:
        /**
         * @brief Constructs a HelpProcessor.
         * @param help The help message string to be displayed.
         * @param logger A logger instance.
         */
        explicit HelpProcessor(std::string_view help, Logger &logger);

        /**
         * @brief Processes the request by printing the help message to the console.
         */
        void Process() override;
    };
}

#endif //REQUEST_PROCESSOR_HPP
