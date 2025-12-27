#include "RequestProcessor.hpp"

#include <iostream>

netmap::HelpProvider::HelpProvider(std::string help)
    : help_(std::move(help)) {
}

void netmap::HelpProvider::Process() {
    std::cout << help_ << std::endl;
}
