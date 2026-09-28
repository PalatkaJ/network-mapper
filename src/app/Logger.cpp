#include "app/Logger.hpp"
#include <chrono>
#include <iostream>

void Logger::VerboseLog(std::string_view msg) const {
    if (verbose_) {
        std::cerr << msg << std::endl;
    }
}

void Logger::Log(std::string_view msg) const {
    *out_ << msg << std::endl;
}

Logger::Logger(bool verbose, std::unique_ptr<std::ostream> output_stream)
    : verbose_(verbose), managed_out_(std::move(output_stream)) {
    out_ = managed_out_ == nullptr ? &std::cout : &*managed_out_;
}