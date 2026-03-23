#include "TracerouteResultPrinter.hpp"
#include <iomanip>
#include <sstream>

netmap::TracerouteResultPrinter::TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, Logger &logger)
    : hops_(hops), dest_hit_(dest_hit), ResultPrinter(logger) {}

void netmap::TracerouteResultPrinter::PrintHeader(std::stringstream& ss, size_t width, const char main_sep, const char sub_sep) const {
    ss << " TRACEROUTE REPORT" << std::endl;
    ss << std::string(width, main_sep) << std::endl;
    ss << " Status: " << (dest_hit_ ? "Destination Reached" : "Destination Unreachable / Timeout") << std::endl;
    ss << " Max Hops: " << MAX_HOPS << std::endl;
    ss << std::string(width, sub_sep) << std::endl;
}

void netmap::TracerouteResultPrinter::PrintBody(std::stringstream& ss, const size_t width, const char sub_sep) const {
    int lastValidIndex = -1;
    for (int i = static_cast<int>(hops_.size()) - 1; i >= 0; --i) {
        if (hops_[i] != pcpp::IPv4Address::Zero) {
            lastValidIndex = i;
            break;
        }
    }

    if (lastValidIndex == -1) {
        ss << " No hops were recorded during the trace." << std::endl;
        return;
    }

    const size_t hop_width = 6;

    ss << std::left
       << std::setw(hop_width) << " Hop"
       << " IP Address" << std::endl;
    ss << std::string(width, sub_sep) << std::endl;

    // we are sure the index is non-negative valid
    lastValidIndex = static_cast<size_t>(lastValidIndex);
    for (size_t i = 0; i <= lastValidIndex; ++i) {
        ss << " " << std::left << std::setw(hop_width - 1) << (i + 1);

        if (hops_[i] == pcpp::IPv4Address::Zero) {
            ss << "*" << std::endl;
        } else {
            ss << hops_[i].toString() << std::endl;
        }
    }
}

void netmap::TracerouteResultPrinter::Print() const {
    std::stringstream ss;
    const size_t width = 60;
    const char main_sep = '=';
    const char sub_sep = '-';

    PrintHeader(ss, width, main_sep, sub_sep);
    PrintBody(ss, width, sub_sep);

    ss << std::string(width, main_sep) << std::endl;

    logger_.Log(ss.str());
}