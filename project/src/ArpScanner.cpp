#include "ArpScanner.hpp"

#include <IPv4Layer.h>

#include "EthLayer.h"
#include "Packet.h"

pcpp::IPv4Address netmap::ArpScanner::GetStartingIpAddress() const {
    auto starting_ip = wrappedDev_.device->getIPv4Address() & wrappedDev_.netmask;

    IncrementIpAddress(starting_ip); // increment because x.y.z.0 is reserved for the network itself (not a valid host ip)
    return starting_ip;
}

// maybe define operator for this
void netmap::ArpScanner::IncrementIpAddress(pcpp::IPv4Address& ip) {
    // net to host and increment
    uint32_t ip_h = ntohl(ip.toInt()) + 1;

    // back to net
    ip = htonl(ip_h);
}

void netmap::ArpScanner::ProcessIp(const pcpp::IPv4Address &ip) const {
    pcpp::ArpRequest request{
        wrappedDev_.device->getMacAddress(),
        wrappedDev_.device->getIPv4Address(),
        ip,
    };

    pcpp::EthLayer ethLayer(wrappedDev_.device->getMacAddress(), pcpp::MacAddress::Broadcast);
    pcpp::ArpLayer arpLayer(request);

    pcpp::Packet arpPacket(100); // create a packet of capacity 100 - this will grow automatically

    arpPacket.addLayer(&ethLayer);
    arpPacket.addLayer(&arpLayer);

    arpPacket.computeCalculateFields();

    wrappedDev_.device->sendPacket(*arpPacket.getRawPacket());
}

uint32_t netmap::ArpScanner::GetHostIntFromNetIp(const pcpp::IPv4Address &ip) {
    return ntohl(ip.toInt());
}

netmap::ArpScanner::ArpScanner(PcapLiveDeviceWrapper &wrappedDev): wrappedDev_(wrappedDev) {}


void netmap::ArpScanner::Process() const {
    auto current_ip = GetStartingIpAddress();

    uint32_t current_ip_int;

    wrappedDev_.device->open();

    while ((GetHostIntFromNetIp(current_ip) | GetHostIntFromNetIp(wrappedDev_.netmask)) < UINT_MAX) {
        ProcessIp(current_ip);

        IncrementIpAddress(current_ip);
    }


    pcpp::ArpFilter arp_filter{pcpp::ARP_REPLY};
    wrappedDev_.device->setFilter(arp_filter);

    pcpp::RawPacketVector packets;
    wrappedDev_.device->startCapture(packets);

    std::this_thread::sleep_for(static_cast<std::chrono::seconds>(5));
    wrappedDev_.device->stopCapture();

    std::ranges::for_each(packets.begin(), packets.end(), [](auto &packet) {
        pcpp::Packet parsed_packet{packet};
        auto eth_layer = parsed_packet.getLayerOfType<pcpp::EthLayer>();
        //auto ip_layer = parsed_packet.getLayerOfType<pcpp::IPv4Layer>();
        std::cout << "source mac: " << eth_layer->getSourceMac()
        << "; dest mac: " << eth_layer->getDestMac() << std::endl;
    });

    wrappedDev_.device->close();
}


