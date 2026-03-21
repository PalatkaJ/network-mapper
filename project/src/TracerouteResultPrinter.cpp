#include "TracerouteResultPrinter.hpp"
#include "ResultPrinter.hpp"

netmap::TracerouteResultPrinter::TracerouteResultPrinter(const std::array<pcpp::IPv4Address, MAX_HOPS>& hops, bool dest_hit, Logger &logger)
    : hops_(hops), dest_hit_(dest_hit), ResultPrinter(logger) {}

void netmap::TracerouteResultPrinter::Print() const {

    logger_.Log("Traceroute Results:");

    // 1. Najdeme index posledního prvku, který není defaultně konstruovaný
    int lastValidIndex = -1;
    for (int i = static_cast<int>(hops_.size()) - 1; i >= 0; --i) {
        if (hops_[i] != pcpp::IPv4Address::Zero) {
            lastValidIndex = i;
            break;
        }
    }

    // Pokud jsme nenašli vůbec nic
    if (lastValidIndex == -1) {
        logger_.Log("No hops recorded.");
        return;
    }

    // 2. Iterujeme pouze do nalezeného posledního prvku
    for (int i = 0; i <= lastValidIndex; ++i) {
        std::string hopId = std::to_string(i + 1) + ": ";

        if (hops_[i] == pcpp::IPv4Address::Zero) {
            // Pokud je adresa prázdná, vypíšeme hvězdičky
            logger_.Log(hopId + "* * *");
        } else {
            // Jinak vypíšeme IP adresu
            logger_.Log(hopId + hops_[i].toString());
        }
    }

    // 3. Volitelné: Informace o tom, zda jsme dosáhli cíle
    if (!dest_hit_) {
        logger_.Log("Did not reach the destination (timed out).");
    }
}
