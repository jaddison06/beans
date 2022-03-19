#pragma once

#include <stdint.h>

#include <chrono>
#include <thread>
#include <functional>

namespace beans {
    typedef uint8_t UniverseData[512];

    struct DMXData {
        uint8_t* data;
        uint8_t length;
    };

    // A DMXInterface is responsible for a SINGLE UNIVERSE of DMX data
    // It should start continuously outputting DMX when it's constructed, and finish
    // when it's destroyed.
    class DMXInterface {
        public:
            ~DMXInterface();
        
            virtual void SetLevels(uint16_t addr, DMXData data) = 0;

            void SendNow();
        
        protected:
            void StartSending(std::function<void()> SendCB, std::chrono::milliseconds keepaliveInterval = std::chrono::milliseconds(1000));
        
        private:
            bool quit = false;
            std::thread keepaliveThread;

            std::function<void()> SendCB;

            void KeepaliveLoop(std::chrono::milliseconds keepaliveInterval);

    };
}