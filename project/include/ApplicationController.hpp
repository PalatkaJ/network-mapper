#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"
#include "RequestProcessor.hpp"
#include "Logger.hpp"

class ApplicationController {
    std::unique_ptr<Logger> logger_;

    void InitializeLogger(const netmap::UserRequest &request);

    [[nodiscard]] static std::unique_ptr<netmap::UserRequest> ParseUserRequest(const cxxopts::ParseResult &result) ;
    [[nodiscard]] static bool ValidateUserRequest(const netmap::UserRequest &request);

public:
    [[nodiscard]] std::unique_ptr<netmap::RequestProcessor> GetRequestedProcessor(const netmap::UserRequest &user_request, const cxxopts::Options &options) const;

    void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result);
};

#endif //APPLICATION_CONTROLLER_HPP
