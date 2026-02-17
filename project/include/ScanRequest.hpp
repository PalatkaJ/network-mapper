#ifndef SCAN_REQUEST_HPP
#define SCAN_REQUEST_HPP
#include <cstdint>
#include <string>


struct ScanRequest {
    std::string interface_name;
    /*
    uint16_t port = 0;
    int timeout_ms = 500;
    */
    bool verbose = false;

    [[nodiscard]] bool isValid() const;
};

inline bool ScanRequest::isValid() const {
    return !interface_name.empty();
}


#endif //SCAN_REQUEST_HPP
