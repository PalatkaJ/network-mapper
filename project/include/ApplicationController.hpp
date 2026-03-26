#ifndef APPLICATION_CONTROLLER_HPP
#define APPLICATION_CONTROLLER_HPP
#include "cxxopts.hpp"
#include "Logger.hpp"

class ApplicationController {
    std::unique_ptr<Logger> logger_;
public:
    void Run(const cxxopts::Options &options, const cxxopts::ParseResult &result) const;
};

#endif //APPLICATION_CONTROLLER_HPP
