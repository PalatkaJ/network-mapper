#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"
#include "../RequestProcessors/RequestProcessor.hpp"

namespace netmap {
    class ApplicationController {
    public:
        static std::unique_ptr<RequestProcessor> GetRequestedProcessor(const cxxopts::Options &options,
                                                               const cxxopts::ParseResult &result);

        static void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result);
    };
}


#endif //APPLICATION_CONTROLLER_HPP
