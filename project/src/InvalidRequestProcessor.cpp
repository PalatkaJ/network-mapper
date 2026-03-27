#include "InvalidRequestProcessor.hpp"
#include "cxxopts.hpp"

netmap::InvalidRequestProcessor::InvalidRequestProcessor(Logger &logger)
    : RequestProcessor(logger) {
}


void netmap::InvalidRequestProcessor::Process() {
    throw cxxopts::exceptions::specification("Invalid arguments");
}