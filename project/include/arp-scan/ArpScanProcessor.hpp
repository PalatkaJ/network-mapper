#ifndef ARP_SCAN_PROCESSOR_HPP
#define ARP_SCAN_PROCESSOR_HPP

#include "app/RequestProcessor.hpp"
#include "app/UserRequest.hpp"

#include <ifaddrs.h>
#include <PcapLiveDevice.h>

#include <string>

namespace netmap {
    /**
     * @brief A request processor for executing an ARP scan.
     *
     * This class implements the RequestProcessor interface and encapsulates the
     * high-level logic for setting up and running a network scan for active
     * devices using ARP.
     */
    class ArpScanProcessor final : public RequestProcessor {
        const UserRequest &user_request_;

        static bool IsTargetIfa(const ifaddrs *ifa, const std::string &devName);

        static pcpp::IPv4Address GetDeviceNetmask(const pcpp::PcapLiveDevice &dev);

    public:
        /**
         * @brief Constructs an ArpScanProcessor.
         * @param user_request The user's configuration for the scan.
         * @param logger A logger instance for logging messages.
         */
        explicit ArpScanProcessor(const UserRequest &user_request, Logger &logger);

        /**
         * @brief Executes the ARP scan process.
         *
         * This method orchestrates the entire scan: finding the device, running
         * the ArpScanner, and printing the results.
         */
        void Process() override;
    };
}


#endif //ARP_SCAN_PROCESSOR_HPP
