#include "ArpScanner.hpp"

#include <IPv4Layer.h>
#include <arpa/inet.h>

#include <utility>

#include "EthLayer.h"
#include "Packet.h"
#include "ArpReplyHandler.hpp"
#include "Logger.hpp"
#include "MacVendorMapper.hpp"

pcpp::IPv4Address netmap::ArpScanner::GetStartingIpAddress() const {
    auto starting_ip = wrappedDev_.device->getIPv4Address() & wrappedDev_.netmask;

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
        wrappedDev_.device->getMacAddress(),
        wrappedDev_.device->getIPv4Address(),
        ip,
    };

    pcpp::EthLayer eth_layer(wrappedDev_.device->getMacAddress(), pcpp::MacAddress::Broadcast);
    pcpp::ArpLayer arp_layer(request);

    pcpp::Packet arp_packet(100); // create a packet of capacity 100 - this will grow automatically

    arp_packet.addLayer(&eth_layer);
    arp_packet.addLayer(&arp_layer);

    arp_packet.computeCalculateFields();

    wrappedDev_.device->sendPacket(*arp_packet.getRawPacket());
}

uint32_t netmap::ArpScanner::GetHostIntFromNetIp(const pcpp::IPv4Address &ip) {
    return ntohl(ip.toInt());
}

void netmap::ArpScanner::SendArpRequests() const {
    auto current_ip = GetStartingIpAddress();

    logger_.VerboseLog("Sending arp requests...");
    // this would look really cool if I could do sth like for (auto ip: available_addresses) {...}
    while ((GetHostIntFromNetIp(current_ip) | GetHostIntFromNetIp(wrappedDev_.netmask)) < UINT_MAX) {
        BuildAndSendArpPacket(current_ip);

        IncrementIpAddress(current_ip);
    }
}

netmap::ArpScanner::ArpScanner(PcapLiveDeviceWrapper &wrappedDev, MacVendorMapper& mac_vendor_mapper, Logger& logger,const UserRequest &user_request)
    : wrappedDev_(wrappedDev), mac_vendor_mapper_(mac_vendor_mapper), logger_(logger), user_request_(user_request) {}

void netmap::ArpScanner::PrepareDeviceForArpCapture() const {
    logger_.VerboseLog("Preparing device for arp capture...");
    pcpp::ArpFilter arp_filter{pcpp::ARP_REPLY};
    wrappedDev_.device->setFilter(arp_filter);
}

void netmap::ArpScanner::OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie) {
    const pcpp::Packet parsed_packet{rawPacket};

    const auto reply_handler = static_cast<ArpReplyHandler *>(cookie);

    reply_handler->ProcessArpReply(parsed_packet);
}

std::vector<netmap::ArpDeviceInfo> netmap::ArpScanner::ScanNetwork() {
    wrappedDev_.device->open();

    PrepareDeviceForArpCapture();
    ArpReplyHandler stats{mac_vendor_mapper_, logger_};
    logger_.VerboseLog("Starting network scan...");
    wrappedDev_.device->startCapture(OnArpReplyCapture, &stats);

    SendArpRequests();

    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(user_request_.timeout_ms));
    wrappedDev_.device->stopCapture();
    wrappedDev_.device->close();

    logger_.VerboseLog("Finished network scan...");
    return stats.GetArpDevices();
}


