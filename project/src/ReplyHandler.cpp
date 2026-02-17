#include "ReplyHandler.hpp"

#include <iostream>
#include <IPv4Layer.h>

#include "ArpLayer.h"
#include "Packet.h"

void netmap::ReplyHandler::ProcessArpReply(const pcpp::Packet &parsedPacket) const {
    auto arp_layer = parsedPacket.getLayerOfType<pcpp::ArpLayer>();
    std::cout << "source IPv4: " << arp_layer->getSenderIpAddr()
    << "; source mac: " << arp_layer->getSenderMacAddress() << std::endl;
}
