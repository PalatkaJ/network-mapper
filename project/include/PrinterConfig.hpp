#ifndef PRINTER_CONFIG_HPP
#define PRINTER_CONFIG_HPP

#include <cstddef>

namespace netmap {
    struct PrinterConfig {
        const char main_sep = '=';
        const char sub_sep = '-';
        const size_t width = 80;
    };
}

#endif //PRINTER_CONFIG_HPP