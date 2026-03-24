#include "ResultPrinter.hpp"

#include <iostream>

netmap::ResultPrinter::ResultPrinter(Logger &logger, PrinterConfig&& printer_config)
    : logger_(logger), printer_config_(std::move(printer_config)) {}

void netmap::ResultPrinter::Print() const {
    std::stringstream ss;

    ss << std::string(printer_config_.width, printer_config_.main_sep) << std::endl;
    ss << GetTitle() << std::endl;
    ss << std::string(printer_config_.width, printer_config_.main_sep) << std::endl;

    PrintHeader(ss);
    ss << std::string(printer_config_.width, printer_config_.sub_sep) << std::endl;
    PrintBody(ss);

    ss << std::string(printer_config_.width, printer_config_.main_sep) << std::endl;

    logger_.Log(ss.str());
}
