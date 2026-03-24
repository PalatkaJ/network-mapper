#ifndef NETWORK_MAPPER_PRINTERCONFIG_HPP
#define NETWORK_MAPPER_PRINTERCONFIG_HPP

#include <cstddef>

namespace netmap {
    struct PrinterConfig {
        const char main_sep = '=';
        const char sub_sep = '-';
        const size_t width = 80;
    };
}

#endif //NETWORK_MAPPER_PRINTERCONFIG_HPP