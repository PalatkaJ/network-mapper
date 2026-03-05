#include "RequestProcessor.hpp"

#include <iostream>

netmap::HelpProcessor::HelpProcessor(std::string help)
    : help_(std::move(help)) {
}

void netmap::HelpProcessor::Process() {
    std::cout << help_ << std::endl;
}
