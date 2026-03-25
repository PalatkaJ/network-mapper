#include "TracerouteResultPrinter.hpp"
#include <iomanip>
#include <sstream>

netmap::TracerouteResultPrinter::TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, pcpp::IPv4Address dest_ip, Logger &logger, PrinterConfig printer_config)
    :  ResultPrinter(logger, std::move(printer_config)), dest_ip_(dest_ip), hops_(hops), dest_hit_(dest_hit) {}

void netmap::TracerouteResultPrinter::PrintHeader(std::stringstream& ss) const {
    ss << " Destination IP: " << dest_ip_.toString() << std::endl;
    ss << " Status:         " << (dest_hit_ ? "Destination Reached" : "Destination Unreachable / Timeout") << std::endl;
    ss << " Max Hops:       " << MAX_HOPS << std::endl;
}

void netmap::TracerouteResultPrinter::PrintBody(std::stringstream& ss) const {
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

    for (;hops_[lastValidIndex] == dest_ip_; --lastValidIndex) {}
    ++lastValidIndex;

    const size_t hop_width = 6;

    ss << std::left
       << std::setw(hop_width) << " Hop"
       << " IP Address" << std::endl;
    ss << std::string(printer_config_.width, printer_config_.sub_sep) << std::endl;

    // surely the index is non-negative and valid
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