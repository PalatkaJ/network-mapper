#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <ostream>
#include <memory>
#include <string_view>

/**
 * @brief Provides a simple logging mechanism.
 *
 * This class handles logging to a specified output stream, with support for
 * a "verbose" mode that can be enabled or disabled.
 */
class Logger {
    bool verbose_;
    std::unique_ptr<std::ostream> managed_out_;
    std::ostream *out_;

public:
    /**
     * @brief Constructs a Logger instance.
     * @param verbose Enables verbose logging if true.
     * @param output_stream A unique_ptr to the output stream where logs will be written.
     */
    Logger(bool verbose, std::unique_ptr<std::ostream> output_stream);

    /**
     * @brief Logs a message, but only if verbose mode is enabled.
     * @param msg The message to log.
     */
    void VerboseLog(std::string_view msg) const;

    /**
     * @brief Logs a message unconditionally.
     *
     * Note that this is used as the main output print.
     * @param msg The message to log.
     */
    void Log(std::string_view msg) const;
};

#endif //LOGGER_HPP
