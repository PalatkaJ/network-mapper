#include "traceroute/IcmpReplyHandler.hpp"
#include <arpa/inet.h>

#include <IcmpLayer.h>

void netmap::IcmpReplyHandler::ProcessIcmpReply(pcpp::IcmpLayer *icmp_layer) {
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

void netmap::IcmpReplyHandler::ProcessEchoReply(pcpp::IcmpLayer *icmp_layer) {
    auto request_id = icmp_layer->getEchoReplyData()->header->id;
    request_id = ntohs(request_id);
    hit_ips_[request_id] = dynamic_cast<pcpp::IPv4Layer *>(icmp_layer->getPrevLayer())->getSrcIPv4Address(); {
        std::lock_guard lock(mutex_);
        dest_hit_ = true;
    }

    cv_.notify_one();
}

void netmap::IcmpReplyHandler::ProcessTimeExceeded(const pcpp::IcmpLayer *icmp_layer) {
    auto request_id = dynamic_cast<pcpp::IPv4Layer *>(icmp_layer->getNextLayer())->getIPv4Header()->ipId;
    // packety jsou jak matriosky, takhle dostanu ten svuj puvodni request, ale jen ip vrstvu

    hit_ips_[request_id] = dynamic_cast<pcpp::IPv4Layer *>(icmp_layer->getPrevLayer())->getSrcIPv4Address();
}

netmap::IcmpReplyHandler::IcmpReplyHandler(Logger &logger)
    : logger_(logger) {
}

void netmap::IcmpReplyHandler::ProcessIcmpReply(const pcpp::Packet &parsedPacket) {
    auto icmp_layer = parsedPacket.getLayerOfType<pcpp::IcmpLayer>();

    if (icmp_layer != nullptr && !dest_hit_) {
        ProcessIcmpReply(icmp_layer);
    }
}