#include <string>
#include "MacVendorMapper.hpp"

#include <fstream>
#include <MacAddress.h>
#include <ranges>
#include <vector>

#include "Logger.hpp"

netmap::MacVendorMapper::MacVendorMapper(std::string &&csv_filename, Logger &logger)
    : csv_filename_(std::move(csv_filename)), logger_(logger) {
}

void netmap::MacVendorMapper::Map() {
    logger_.VerboseLog(std::format("Parsing {} and mapping mac addresses to corresponding vendors", csv_filename_));

    const auto full_path = std::format("../data/{}", csv_filename_);

    std::ifstream file(full_path);

    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + csv_filename_);
    }

    std::string line;
    // get rid of the header
    (void) std::getline(file, line);

    while (std::getline(file, line)) {
        ProcessLineEntry(line);
    }
}

std::string netmap::MacVendorMapper::ParseVendorName(const std::vector<std::string> &fields, const std::string &entry) {
    std::string vendor_name = fields[VENDOR_NAME_INDEX];

    // ugly name parsing out of the .csv file, this is not a program that nicely reads and parses csv
    // this is enough for our purposes
    if (auto find = entry.find_first_of('\"'); find != std::string::npos) {
        vendor_name = entry.substr(find + 1, entry.find_last_of('\"') - find - 1);
    }

    return vendor_name;
}

void netmap::MacVendorMapper::ProcessLineEntry(const std::string &entry) {
    auto fields_view = entry | std::views::split(CSV_SEPARATOR);
    auto fields = std::ranges::to<std::vector<std::string> >(fields_view);

    std::string vendor_name = ParseVendorName(fields, entry);

    mac_vendor_map_.emplace(fields[MAC_PREFIX_INDEX], vendor_name);
}

bool netmap::MacVendorMapper::IsLocallyAdministrated(const pcpp::MacAddress mac_address) {
    auto byte_array = mac_address.toByteArray();
    return (byte_array[0] & LOCALLY_ADMINISTERED_MASK) != 0;
}

std::string netmap::MacVendorMapper::GetVendorName(const pcpp::MacAddress mac_address) {
    if (IsLocallyAdministrated(mac_address)) {
        return "Unknown: locally administrated";
    }

    std::string mac_str = mac_address.toString();

    std::ranges::transform(mac_str, mac_str.begin(), [](unsigned char c) {
        return std::toupper(c);
    });

    for (size_t i = 0; i < mac_str.length(); ++i) {
        std::string substr_to_find = mac_str.substr(0, mac_str.length() - i);
        if (auto search = mac_vendor_map_.find(substr_to_find); search != mac_vendor_map_.end()) {
            return search->second;
        }
    }

    return "Unknown";
}