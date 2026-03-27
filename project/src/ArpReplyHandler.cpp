#include "ArpReplyHandler.hpp"

#include <IPv4Layer.h>
#include <format>

#include "ArpLayer.h"
#include "Packet.h"

netmap::ArpReplyHandler::ArpReplyHandler(MacVendorMapper &mac_vendor_mapper, Logger &logger)
    : mac_vendor_mapper_(mac_vendor_mapper), logger_(logger) {
    devices_ = {};
    devices_.reserve(ARP_DEV_RESERVE);
}

void netmap::ArpReplyHandler::ProcessArpReply(const pcpp::Packet &parsedPacket) {
    auto arp_layer = parsedPacket.getLayerOfType<pcpp::ArpLayer>();
    auto sender_mac = arp_layer->getSenderMacAddress();
    auto sender_ip = arp_layer->getSenderIpAddr();

    auto vendor = mac_vendor_mapper_.GetVendorName(sender_mac);

    devices_.emplace_back(sender_mac, sender_ip, std::move(vendor));
}
