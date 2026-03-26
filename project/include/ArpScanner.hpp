#ifndef ARP_SCANNER_HPP
#define ARP_SCANNER_HPP

#include "ArpDeviceInfo.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"
#include "DevWrapperForArpScan.hpp"
#include "UserRequest.hpp"


namespace netmap {
    /**
     * @brief Performs an ARP scan on the local network to discover active devices.
     *
     * This class sends ARP requests to a range of IP addresses on the network
     * and listens for ARP replies to identify which hosts are online.
     */
    class ArpScanner {
        DevWrapperForArpScan &dev_wrapper_;
        MacVendorMapper &mac_vendor_mapper_;
        Logger &logger_;
        const UserRequest &user_request_;

        [[nodiscard]] pcpp::IPv4Address GetStartingIpAddress() const;

        static void IncrementIpAddress(pcpp::IPv4Address &ip);

        void BuildAndSendArpPacket(const pcpp::IPv4Address &ip) const;

        static uint32_t GetHostIntFromNetIp(const pcpp::IPv4Address &ip);

        void SendArpRequests() const;

        void PrepareDeviceForArpCapture() const;

        static void OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie);

    public:
        /**
         * @brief Constructs an ArpScanner.
         * @param dev_wrapper A wrapper for the network device used for scanning.
         * @param mac_vendor_mapper A utility to map MAC addresses to vendor names.
         * @param logger A logger instance for logging messages.
         * @param user_request The user's request configuration.
         */
        explicit ArpScanner(DevWrapperForArpScan &dev_wrapper, MacVendorMapper &mac_vendor_mapper, Logger &logger,
                            const UserRequest &user_request);

        /**
         * @brief Executes the ARP scan.
         *
         * This method orchestrates the sending of ARP requests and the capturing
         * of replies, then compiles the results into a list of discovered devices.
         * @return A vector of ArpDeviceInfo objects, one for each discovered device.
         */
        [[nodiscard]] std::vector<ArpDeviceInfo> ScanNetwork() const;
    };
}


#endif //ARP_SCANNER_HPP
