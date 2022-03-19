#include "SACN.hpp"

#include <stdexcept>

#include "debug/Log.hpp"
#include "debug/assert.hpp"

using namespace beans;

SACNInterface::SACNInterface(std::string source_name, std::string dest, uint16_t universe) {
    if ((sockfd = e131_socket()) < 0) {
        err = E131ErrorCode::SocketInitErr;
        return;
    }

    e131_pkt_init(&packet, universe, 512);

    if (source_name.length() > 63) {
        err = E131ErrorCode::SourceNameTooLong;
        return;
    }
    memcpy(&packet.frame.source_name, source_name.c_str(), source_name.length() + 1);

    if (e131_unicast_dest(&this->dest, dest.c_str(), E131_DEFAULT_PORT) < 0) {
        err = E131ErrorCode::SetUnicastDestFailed;
        return;
    }

    err = E131ErrorCode::Success;

    StartSending(std::bind(&SACNInterface::Send, this));
}

void SACNInterface::SetLevels(uint16_t addr, DMXData data) {
    // check for change - this is SACN, so we don't wanna resend packets if we don't have to.
    if (memcmp(data.data, &packet.dmp.prop_val[addr], data.length) == 0) return;

    memcpy(&packet.dmp.prop_val[addr], data.data, data.length);

    SendNow();
}

void SACNInterface::Send() {
    static int i = 0;
    Log::Info("Sending SACN packet %i", i++);

    auto ret = e131_send(sockfd, &packet, &dest);
    packet.frame.seq_number++;
    if (ret < 0) throw std::runtime_error("e131_send returned error");
}