#include "RouteTracer.hpp"

#include <EthLayer.h>
#include <format>
#include <IPLayer.h>
#include <IPv4Layer.h>
#include <IcmpLayer.h>
#include <PcapLiveDeviceList.h>
#include <NetworkUtils.h>
#include <Packet.h>

#include "IcmpReplyHandler.hpp"

netmap::RouteTracer::RouteTracer(pcpp::IPv4Address source_ip, pcpp::IPv4Address dest_ip, Logger &logger, const UserRequest &user_request)
    :source_ip_(source_ip), dest_ip_(dest_ip), logger_(logger), user_request_(user_request) {}

void netmap::RouteTracer::FindRoute(pcpp::PcapLiveDevice* dev, pcpp::MacAddress gateway_mac) {
    pcpp::EthLayer eth_layer(dev->getMacAddress(), gateway_mac);
    pcpp::IPv4Layer ip_layer(source_ip_, dest_ip_);
    pcpp::IcmpLayer icmp_layer;

    pcpp::Packet packet(100);

    packet.addLayer(&eth_layer);
    packet.addLayer(&ip_layer);
    packet.addLayer(&icmp_layer);

    for (size_t i = 1; i < MAX_HOPS; ++i) {
        packet.getLayerOfType<pcpp::IPv4Layer>()->getIPv4Header()->timeToLive = i;
        packet.getLayerOfType<pcpp::IPv4Layer>()->getIPv4Header()->ipId = i-1;
        packet.getLayerOfType<pcpp::IcmpLayer>()->setEchoRequestData(i-1, 0,0,nullptr,0);
        packet.computeCalculateFields();
        dev->sendPacket(*packet.getRawPacket());
    }
}

void netmap::RouteTracer::OnIcmpPacketCapture(pcpp::RawPacket *rawPacket, const pcpp::PcapLiveDevice *iface, void *cookie) {
    const pcpp::Packet parsed_packet{rawPacket};

    const auto reply_handler = static_cast<IcmpReplyHandler *>(cookie);

    reply_handler->ProcessIcmpReply(parsed_packet);
}

netmap::IcmpReplyHandler netmap::RouteTracer::Execute() {
    logger_.VerboseLog(std::format("finding path (traceroute) for destination ip: {}", dest_ip_.toString()));

    auto *dev = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(source_ip_);

    if (dev == nullptr) {
        throw std::runtime_error{std::format("could not find network interface for destination ip: {}", dest_ip_.toString())};
    }

    IcmpReplyHandler stats{logger_};

    auto net_utils = pcpp::NetworkUtils::getInstance();
    double arp_response_time = 1000.0;

    auto gateaway_mac = net_utils.getMacAddress(dev->getDefaultGateway(), dev, arp_response_time, dev->getMacAddress(), source_ip_);
    logger_.VerboseLog(std::format("resolved gateaway mac to: {}", gateaway_mac.toString()));


    dev->open();
    dev->startCapture(OnIcmpPacketCapture, &stats);

    FindRoute(dev, gateaway_mac);

    std::this_thread::sleep_for(static_cast<std::chrono::milliseconds>(user_request_.timeout_ms));
    dev->stopCapture();
    dev->close();

    return stats;
}
