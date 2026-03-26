#ifndef REQUEST_PROCESSOR_FACTORY_HPP
#define REQUEST_PROCESSOR_FACTORY_HPP
#include "RequestProcessor.hpp"
#include "UserRequest.hpp"

namespace netmap {
    /**
     * @brief A factory for creating RequestProcessor instances.
     *
     * This class centralizes the logic for deciding which type of processor
     * (e.g., ArpScanProcessor, TracerouteProcessor, HelpProcessor) should be
     * created based on the user's command-line arguments.
     */
    class RequestProcessorFactory {
    public:
        /**
         * @brief Creates the appropriate RequestProcessor based on the user's request.
         * @param user_request The user's configuration, parsed from command-line options.
         * @param options The cxxopts::Options object, used for creating the help processor.
         * @param logger A logger instance to be passed to the created processor.
         * @return A std::unique_ptr to the concrete RequestProcessor.
         */
        static std::unique_ptr<RequestProcessor> CreateRequestProcessor(const UserRequest &user_request,
                                                                        const cxxopts::Options &options,
                                                                        Logger &logger);
    };
}

#endif //REQUEST_PROCESSOR_FACTORY_HPP
