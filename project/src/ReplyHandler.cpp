#include "ReplyHandler.hpp"

#include <iostream>
#include <IPv4Layer.h>
#include <format>
#include <sys/socket.h>

#include "ArpLayer.h"
#include "Packet.h"

netmap::ReplyHandler::ReplyHandler(MacVendorMapper& mac_vendor_mapper, Logger &logger)
    :mac_vendor_mapper_(mac_vendor_mapper), logger_(logger) {}

void netmap::ReplyHandler::ProcessArpReply(const pcpp::Packet &parsedPacket) const {
    auto arp_layer = parsedPacket.getLayerOfType<pcpp::ArpLayer>();
    auto sender_mac = arp_layer->getSenderMacAddress();

    auto vendor = mac_vendor_mapper_.GetVendorName(sender_mac);


    logger_.Log(std::format("{}      {}      {}", arp_layer->getSenderIpAddr().toString(),sender_mac.toString(), vendor));
}
