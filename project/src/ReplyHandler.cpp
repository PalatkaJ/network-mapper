#include "ReplyHandler.hpp"

#include <iostream>
#include <IPv4Layer.h>
#include <format>

#include "ArpLayer.h"
#include "Packet.h"

netmap::ReplyHandler::ReplyHandler(Logger &logger)
    :logger_(logger) {}

void netmap::ReplyHandler::ProcessArpReply(const pcpp::Packet &parsedPacket) const {
    auto arp_layer = parsedPacket.getLayerOfType<pcpp::ArpLayer>();
    logger_.Log(std::format("source IPv4: {}; source mac: {}", arp_layer->getSenderIpAddr().toString(),
                             arp_layer->getSenderMacAddress().toString()));
}
