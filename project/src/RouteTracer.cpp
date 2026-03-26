#include "RouteTracer.hpp"

#include <EthLayer.h>
#include <format>
#include <IPLayer.h>
#include <IPv4Layer.h>
#include <IcmpLayer.h>
#include <PcapLiveDeviceList.h>
#include <NetworkUtils.h>
#include <Packet.h>

#include "DevWrapperForTraceroute.hpp"
#include "IcmpReplyHandler.hpp"
#include "SystemUtils.h"
#include "TracerouteResult.hpp"

netmap::RouteTracer::RouteTracer(DevWrapperForTraceroute& dev_wrapper, pcpp::IPv4Address source_ip, pcpp::IPv4Address dest_ip, Logger &logger, const UserRequest &user_request)
    : dev_wrapper_(dev_wrapper), source_ip_(source_ip), dest_ip_(dest_ip), logger_(logger), user_request_(user_request) {}

void netmap::RouteTracer::FindRoute() {
    pcpp::EthLayer eth_layer(dev_wrapper_.device->getMacAddress(), dev_wrapper_.gateway_mac);
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
        dev_wrapper_.device->sendPacket(*packet.getRawPacket());
        std::chrono::milliseconds(100);
    }
}

void netmap::RouteTracer::OnIcmpPacketCapture(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *iface, void *cookie) {
    const pcpp::Packet parsed_packet{rawPacket};

    const auto reply_handler = static_cast<IcmpReplyHandler *>(cookie);

    reply_handler->ProcessIcmpReply(parsed_packet);
}

netmap::TracerouteResult netmap::RouteTracer::Execute() {
    IcmpReplyHandler stats{logger_};

    dev_wrapper_.device->open();
    
    logger_.VerboseLog("Start capturing ICMP replies");
    dev_wrapper_.device->startCapture(OnIcmpPacketCapture, &stats);

    logger_.VerboseLog("Sending ICMP requests");
    FindRoute();
    logger_.VerboseLog("All ICMP requests sent");
    
    logger_.VerboseLog("Waiting for ICMP replies");
    std::unique_lock lock(stats.GetMutex());
    stats.GetCondVar().wait_for(lock, std::chrono::milliseconds(user_request_.timeout_ms), [&stats]{ return stats.IsDestHit(); });

    logger_.VerboseLog("ICMP replies received, stop capture");
    dev_wrapper_.device->stopCapture();
    dev_wrapper_.device->close();

    return {stats.GetHitIps(), dest_ip_, stats.IsDestHit()};
}
