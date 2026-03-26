#include "ArpScanner.hpp"

#include <IPv4Layer.h>
#include <arpa/inet.h>


#include "EthLayer.h"
#include "Packet.h"
#include "ArpReplyHandler.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"

pcpp::IPv4Address netmap::ArpScanner::GetStartingIpAddress() const {
    auto starting_ip = dev_wrapper_.device->getIPv4Address() & dev_wrapper_.netmask;

    IncrementIpAddress(starting_ip); // increment because x.y.z.0 is reserved for the network itself (not a valid host ip)
    return starting_ip;
}

// maybe define operator for this
void netmap::ArpScanner::IncrementIpAddress(pcpp::IPv4Address& ip) {
    // net to host and increment
    uint32_t ip_h = GetHostIntFromNetIp(ip) + 1;

    // back to net
    ip = htonl(ip_h);
}

// this is one function and not two because we would have to allocate a lot of stuff
// on the heap to return the built packet from this function, since there
// are a lot of dependencies (such as the layers)
void netmap::ArpScanner::BuildAndSendArpPacket(const pcpp::IPv4Address &ip) const {
    pcpp::ArpRequest request{
        dev_wrapper_.device->getMacAddress(),
        dev_wrapper_.device->getIPv4Address(),
        ip,
    };

    pcpp::EthLayer eth_layer(dev_wrapper_.device->getMacAddress(), pcpp::MacAddress::Broadcast);
    pcpp::ArpLayer arp_layer(request);

    pcpp::Packet arp_packet(100); // create a packet of capacity 100 - this will grow automatically

    arp_packet.addLayer(&eth_layer);
    arp_packet.addLayer(&arp_layer);

    arp_packet.computeCalculateFields();

    dev_wrapper_.device->sendPacket(*arp_packet.getRawPacket());
}

uint32_t netmap::ArpScanner::GetHostIntFromNetIp(const pcpp::IPv4Address &ip) {
    return ntohl(ip.toInt());
}

void netmap::ArpScanner::SendArpRequests() const {
    auto current_ip = GetStartingIpAddress();

    while ((GetHostIntFromNetIp(current_ip) | GetHostIntFromNetIp(dev_wrapper_.netmask)) < UINT_MAX) {
        BuildAndSendArpPacket(current_ip);

        IncrementIpAddress(current_ip);
    }
}

netmap::ArpScanner::ArpScanner(DevWrapperForArpScan &dev_wrapper, MacVendorMapper& mac_vendor_mapper, Logger& logger,const UserRequest &user_request)
    : dev_wrapper_(dev_wrapper), mac_vendor_mapper_(mac_vendor_mapper), logger_(logger), user_request_(user_request) {}

void netmap::ArpScanner::PrepareDeviceForArpCapture() const {
    pcpp::ArpFilter arp_filter{pcpp::ARP_REPLY};
    dev_wrapper_.device->setFilter(arp_filter);
}

void netmap::ArpScanner::OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie) {
    const pcpp::Packet parsed_packet{rawPacket};

    const auto reply_handler = static_cast<ArpReplyHandler *>(cookie);

    reply_handler->ProcessArpReply(parsed_packet);
}

std::vector<netmap::ArpDeviceInfo> netmap::ArpScanner::ScanNetwork() const {
    dev_wrapper_.device->open();

    logger_.VerboseLog("Preparing device for ARP capture");
    PrepareDeviceForArpCapture();
    ArpReplyHandler stats{mac_vendor_mapper_, logger_};

    logger_.VerboseLog("Start capturing ARP replies");
    dev_wrapper_.device->startCapture(OnArpReplyCapture, &stats);

    logger_.VerboseLog("Sending ARP requests");
    SendArpRequests();
    logger_.VerboseLog("All ARP requests sent");

    logger_.VerboseLog("Waiting for ARP replies");
    std::this_thread::sleep_for(std::chrono::milliseconds(user_request_.timeout_ms));

    logger_.VerboseLog("ARP replies received, stop capture");
    dev_wrapper_.device->stopCapture();
    dev_wrapper_.device->close();

    return stats.GetArpDevices();
}


