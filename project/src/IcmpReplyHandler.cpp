#include "IcmpReplyHandler.hpp"

#include <IcmpLayer.h>

netmap::IcmpReplyHandler::IcmpReplyHandler(Logger &logger)
    :logger_(logger) {}

void netmap::IcmpReplyHandler::ProcessIcmpReply(const pcpp::Packet &parsedPacket) {
    auto icmp_layer = parsedPacket.getLayerOfType<pcpp::IcmpLayer>();

    if (icmp_layer != nullptr && icmp_layer->getEchoReplyData() != nullptr) {
        logger_.VerboseLog(icmp_layer->toString());
    }
}
