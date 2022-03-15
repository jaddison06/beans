#include "SACN.hpp"

#include <stdexcept>

using namespace beans;

SACNInterface::SACNInterface(std::string source_name, std::string dest, uint16_t universe) : DMXInterface() {
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

    sendThread = std::thread([=](){SendLoop();});
}

SACNInterface::~SACNInterface() {
    quit = true;
    sendThread.join();
}

void SACNInterface::SetLevels(DMXData data) {
    memcpy(&packet.dmp.prop_val[1], data.data, data.length);
    Send();
}

// eek ouch yuck
// i wanna call Send() from SetLevels so it gets called whenever the data changes,
// but at the same time it should lowkey be on a different thread.
//
// SendLoop() also needs to happen every second-ish as a keepalive

void SACNInterface::Send() {
    auto ret = e131_send(sockfd, &packet, &dest);
    packet.frame.seq_number++;
    if (ret < 0) throw std::runtime_error("e131_send returned error");
}

void SACNInterface::SendLoop() {
    while (!quit) {
       Send();

        // E1.31 mandates a keepalive packet every 1.5 secs, so send every second to be safe.
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}