#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <ostream>

#include "ScanRequest.hpp"

class Logger {
    bool verbose_;
    std::unique_ptr<std::ostream> managed_out_;
    std::ostream* out_;

public:
    Logger(bool verbose, std::unique_ptr<std::ostream> output_stream);

    void VerboseLog(std::string_view msg) const;
    void Log(std::string_view msg) const;
};

#endif //LOGGER_HPP
