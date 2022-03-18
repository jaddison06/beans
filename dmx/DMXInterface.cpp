#include "DMXInterface.hpp"

using namespace beans;

DMXInterface::~DMXInterface() {
    quit = true;
    keepaliveThread.join();
}

void DMXInterface::StartSending(std::function<void()> SendCB, std::chrono::milliseconds keepaliveInterval = std::chrono::milliseconds(1000)) {
    this->SendCB = SendCB;
    keepaliveThread = std::thread([&](){ KeepaliveLoop(keepaliveInterval); });
}

// not ideal bc it'll take however many ms to register the quit
void DMXInterface::KeepaliveLoop(std::chrono::milliseconds keepaliveInterval) {
    while (!quit) {
        SendCB();
        std::this_thread::sleep_for(keepaliveInterval);
    }
}

void DMXInterface::SendNow() {
    std::thread(SendCB);
}