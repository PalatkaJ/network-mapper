#include "RequestProcessor.hpp"

#include <iostream>

netmap::RequestProcessor::RequestProcessor(Logger &logger)
    : logger_(logger) {}

netmap::HelpProcessor::HelpProcessor(std::string_view help, Logger &logger)
    : RequestProcessor(logger), help_(help) {}

void netmap::HelpProcessor::Process() {
    logger_.Log(help_);
}
