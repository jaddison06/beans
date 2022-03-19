#include "DMXInterface.hpp"

#include "debug/Log.hpp"

using namespace beans;

DMXInterface::~DMXInterface() {
    quit = true;
    keepaliveThread.join();
}

void DMXInterface::StartSending(std::function<void()> SendCB, std::chrono::milliseconds keepaliveInterval) {
    this->SendCB = SendCB;
    keepaliveThread = std::thread([=](){ Log::Info("Keepalive lambda"); KeepaliveLoop(keepaliveInterval); });
}

// not ideal bc it'll take however many ms to register the quit
void DMXInterface::KeepaliveLoop(std::chrono::milliseconds keepaliveInterval) {
    while (!quit) {
        SendCB();
        std::this_thread::sleep_for(keepaliveInterval);
    }
}

void DMXInterface::SendNow() {
    Log::Warning("SendNow called");
    std::thread(SendCB);
}