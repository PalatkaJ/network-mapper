
#include "Logger.hpp"

void Logger::VerboseLog(std::string_view msg) const {
    if (verbose_) {
        output_stream_ << msg << std::endl;
    }
}

void Logger::Log(std::string_view msg) const {
    output_stream_ << msg << std::endl;
}

Logger::Logger(bool verbose, std::ostream &output_stream)
: verbose_(verbose), output_stream_(output_stream) {}





