#include "IcmpReplyHandler.hpp"

#include <IcmpLayer.h>

void netmap::IcmpReplyHandler::ProcessIcmpReply(const pcpp::IcmpLayer *icmp_layer) {
    switch (icmp_layer->getIcmpHeader()->type) {
        case pcpp::ICMP_ECHO_REQUEST:
            // the outcoming request
            break;
        case pcpp::ICMP_TIME_EXCEEDED:
            ProcessTimeExceeded(icmp_layer);
            break;
        case pcpp::ICMP_ECHO_REPLY:
            ProcessEchoReply(icmp_layer);
            break;
        default:
            break;
    }
}

void netmap::IcmpReplyHandler::ProcessEchoReply(const pcpp::IcmpLayer *icmp_layer) {
    dest_hit_ = true;
}

void netmap::IcmpReplyHandler::ProcessTimeExceeded(const pcpp::IcmpLayer *icmp_layer) {
    hit_ips_.emplace_back(dynamic_cast<pcpp::IPv4Layer*>(icmp_layer->getPrevLayer())->getSrcIPv4Address());
}

netmap::IcmpReplyHandler::IcmpReplyHandler(Logger &logger)
    :logger_(logger) {}

void netmap::IcmpReplyHandler::ProcessIcmpReply(const pcpp::Packet &parsedPacket) {
    auto icmp_layer = parsedPacket.getLayerOfType<pcpp::IcmpLayer>();

    if (icmp_layer != nullptr) {
        ProcessIcmpReply(icmp_layer);
    }
}
