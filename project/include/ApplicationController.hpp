#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"
#include "RequestProcessor.hpp"
#include "Logger.hpp"

class ApplicationController {
    std::unique_ptr<Logger> logger_;

    void InitializeLogger(UserRequest *request);

    [[nodiscard]] static std::unique_ptr<UserRequest> ParseUserRequest(const cxxopts::ParseResult &result) ;


public:
    [[nodiscard]] std::unique_ptr<netmap::RequestProcessor> GetRequestedProcessor(UserRequest *user_request, const cxxopts::Options &options) const;

    void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result);
};

#endif //APPLICATION_CONTROLLER_HPP
