#ifndef SCAN_REQUEST_HPP
#define SCAN_REQUEST_HPP
#include <cstdint>
#include <string>


struct ScanRequest {
    std::string interface_name;
    std::string output_filename;
    uint32_t timeout_ms = 5000;
    /*
    uint16_t port = 0;
    */
    bool verbose = false;

    [[nodiscard]] bool isValid() const;
};

inline bool ScanRequest::isValid() const {
    return !interface_name.empty();
}


#endif //SCAN_REQUEST_HPP
