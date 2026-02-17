#include "ArpScanner.hpp"

#include <IPv4Layer.h>
#include <arpa/inet.h>

#include "EthLayer.h"
#include "Packet.h"
#include "ReplyHandler.hpp"
#include "Logger.hpp"

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

    pcpp::EthLayer ethLayer(wrappedDev_.device->getMacAddress(), pcpp::MacAddress::Broadcast);
    pcpp::ArpLayer arpLayer(request);

    pcpp::Packet arp_packet(100); // create a packet of capacity 100 - this will grow automatically

    arp_packet.addLayer(&ethLayer);
    arp_packet.addLayer(&arpLayer);

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

netmap::ArpScanner::ArpScanner(PcapLiveDeviceWrapper &wrappedDev, Logger& logger): wrappedDev_(wrappedDev), logger_(logger) {}

void netmap::ArpScanner::PrepareDeviceForArpCapture() const {
    logger_.VerboseLog("Preparing device for arp capture...");
    pcpp::ArpFilter arp_filter{pcpp::ARP_REPLY};
    wrappedDev_.device->setFilter(arp_filter);
}

void netmap::ArpScanner::OnArpReplyCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie) {
    const pcpp::Packet parsed_packet{rawPacket};

    const auto reply_handler = static_cast<ReplyHandler *>(cookie);

    reply_handler->ProcessArpReply(parsed_packet);
}

void netmap::ArpScanner::ScanNetwork() const {
    wrappedDev_.device->open();

    PrepareDeviceForArpCapture();
    ReplyHandler stats;
    logger_.VerboseLog("Starting network scan...");
    wrappedDev_.device->startCapture(OnArpReplyCapture, &stats);

    SendArpRequests();

    std::this_thread::sleep_for(static_cast<std::chrono::seconds>(5));
    logger_.VerboseLog("Stopping network scan...");
    wrappedDev_.device->stopCapture();

    wrappedDev_.device->close();
}


