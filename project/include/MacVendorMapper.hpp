#ifndef MAC_VENDOR_MAPPER_HPP
#define MAC_VENDOR_MAPPER_HPP
#include <MacAddress.h>
#include <unordered_map>

#include "Logger.hpp"

namespace netmap {

    constexpr uint8_t LOCALLY_ADMINISTERED_MASK = 0x02;
    constexpr char CSV_HEX_SEPARATOR = ':';
    constexpr char CSV_SEPARATOR = ',';
    constexpr size_t MAC_PREFIX_INDEX = 0;
    constexpr size_t VENDOR_NAME_INDEX = 1;
    constexpr size_t CSV_COLUMNS_COUNT = 5;

    class MacVendorMapper {
        std::string csv_filename_;
        Logger& logger_;
        std::unordered_map<std::string, std::string> mac_vendor_map_;

        static std::string ParseVendorName(const std::vector<std::string>& fields, const std::string& entry);
        static bool IsLocallyAdministrated(pcpp::MacAddress mac_address);

        void ProcessLineEntry(const std::string& entry);
    public:
        explicit MacVendorMapper(std::string&& csv_filename, Logger& logger);
        void Map();
        std::string GetVendorName(pcpp::MacAddress mac_address);
    };
}

#endif //MAC_VENDOR_MAPPER_HPP