#ifndef MAC_VENDOR_MAPPER_HPP
#define MAC_VENDOR_MAPPER_HPP
#include <MacAddress.h>
#include <unordered_map>
#include <vector>
#include <string>

#include "Logger.hpp"

namespace netmap {
    constexpr uint8_t LOCALLY_ADMINISTERED_MASK = 0x02;
    constexpr char CSV_HEX_SEPARATOR = ':';
    constexpr char CSV_SEPARATOR = ',';
    constexpr size_t MAC_PREFIX_INDEX = 0;
    constexpr size_t VENDOR_NAME_INDEX = 1;
    constexpr size_t CSV_COLUMNS_COUNT = 5;

    /**
     * @brief Maps MAC address prefixes to manufacturer vendor names.
     *
     * This class parses a CSV file containing MAC address OUI (Organizationally
     * Unique Identifier) data and builds an in-memory map to allow for a quick
     * lookup of a vendor name from a given MAC address.
     */
    class MacVendorMapper {
        std::string csv_filename_;
        Logger &logger_;
        std::unordered_map<std::string, std::string> mac_vendor_map_;

        static std::string ParseVendorName(const std::vector<std::string> &fields, const std::string &entry);

        static bool IsLocallyAdministrated(pcpp::MacAddress mac_address);

        void ProcessLineEntry(const std::string &entry);

    public:
        /**
         * @brief Constructs a MacVendorMapper.
         * @param csv_filename The path to the CSV file with MAC vendor data.
         * @param logger A logger instance for logging messages.
         */
        explicit MacVendorMapper(std::string &&csv_filename, Logger &logger);

        /**
         * @brief Parses the CSV file and populates the internal map.
         *
         * This method must be called before GetVendorName can be used effectively.
         */
        void Map();

        /**
         * @brief Looks up the vendor name for a given MAC address.
         * @param mac_address The MAC address to look up.
         * @return The vendor name if found, or a default string otherwise.
         */
        std::string GetVendorName(pcpp::MacAddress mac_address);
    };
}

#endif //MAC_VENDOR_MAPPER_HPP
