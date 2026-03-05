#include "InvalidRequestProcessor.hpp"

netmap::InvalidRequestProcessor::InvalidRequestProcessor(Logger &logger)
    : logger_(logger){}


void netmap::InvalidRequestProcessor::Process() {
    throw cxxopts::exceptions::specification("Invalid arguments");
}
