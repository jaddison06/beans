#include "DMXInterface.hpp"

#include "debug/Log.hpp"

using namespace beans;

DMXInterface::~DMXInterface() {
    quit = true;
    keepaliveThread.join();
}

void DMXInterface::StartSending(std::function<void()> SendCB, std::chrono::milliseconds keepaliveInterval) {
    this->SendCB = SendCB;
    keepaliveThread = std::thread([=](){ KeepaliveLoop(keepaliveInterval); });
}

// not ideal bc it'll take however many ms to register the quit
void DMXInterface::KeepaliveLoop(std::chrono::milliseconds keepaliveInterval) {
    while (!quit) {
        SendCB();
        std::this_thread::sleep_for(keepaliveInterval);
    }
}

void DMXInterface::SendNow() {
    // wanna execute it in PARALLEL, but spawning a new thread is expensive and stupid and a bitch
    // solution...?
    std::thread(SendCB);
}