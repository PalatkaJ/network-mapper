
#ifndef INVALID_REQUEST_PROCESSOR_HPP
#define INVALID_REQUEST_PROCESSOR_HPP
#include "Logger.hpp"
#include "RequestProcessor.hpp"

namespace netmap {
    /**
     * @brief A request processor for handling invalid user input.
     *
     * This processor is invoked when the user's command-line arguments are
     * determined to be invalid or conflicting. It simply prints an error message.
     */
    class InvalidRequestProcessor final : public RequestProcessor {
    public:
        /**
         * @brief Constructs an InvalidRequestProcessor.
         * @param logger A logger instance for logging the error message.
         */
        explicit InvalidRequestProcessor(Logger &logger);

        /**
         * @brief Logs a message indicating that the user's request is invalid.
         */
        void Process() override;
    };
}

#endif //INVALID_REQUEST_PROCESSOR_HPP
