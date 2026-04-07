#include <fstream>

#include "app/LoggerFactory.hpp"

std::unique_ptr<Logger> netmap::LoggerFactory::CreateLogger(const UserRequest &request) {
    std::unique_ptr<std::ofstream> file_stream = nullptr;

    if (!request.output_filename.empty()) {
        file_stream = std::make_unique<std::ofstream>(request.output_filename);
        if (!file_stream->is_open()) {
            throw std::runtime_error("Could not open output file");
        }
    }

    return std::make_unique<Logger>(request.verbose, std::move(file_stream));
}