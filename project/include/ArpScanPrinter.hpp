#ifndef ARP_SCAN_PRINTER_HPP
#define ARP_SCAN_PRINTER_HPP
#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "DevWrapperForArpScan.hpp"
#include "ResultPrinter.hpp"

namespace netmap {
    /**
     * @brief Formats and prints the results of an ARP scan.
     *
     * This class inherits from ResultPrinter and is specialized for printing
     * information about discovered devices in a clean, tabular format.
     */
    class ArpScanPrinter : public ResultPrinter {
        DevWrapperForArpScan& dev_wrapper_;
        std::vector<ArpDeviceInfo> arp_devices_found_;

    protected:
        /**
         * @brief Prints the main body of the results table.
         * @param ss The string stream to write the output to.
         */
        void PrintBody(std::stringstream &ss) const override;

        /**
         * @brief Prints the header of the results table.
         * @param ss The string stream to write the output to.
         */
        void PrintHeader(std::stringstream &ss) const override;

        /**
         * @brief Gets the title for the results output.
         * @return The title string.
         */
        [[nodiscard]] inline std::string GetTitle() const override;

    public:
        /**
         * @brief Constructs an ArpScanPrinter.
         * @param dev_wrapper The device wrapper used for the scan.
         * @param arp_devices_found A vector of discovered devices to be printed.
         * @param logger A logger instance.
         * @param printer_config Configuration for the printer.
         */
        ArpScanPrinter(DevWrapperForArpScan &dev_wrapper, std::vector<ArpDeviceInfo> arp_devices_found, Logger &logger,
                       PrinterConfig printer_config = PrinterConfig());
    };

    inline std::string ArpScanPrinter::GetTitle() const {
        return " ARP Scan Results";
    }
}

#endif //ARP_SCAN_PRINTER_HPP
