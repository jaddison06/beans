#pragma once

#include <stdint.h>

// lil bit of namespace pollution so includers can sleep
#include <chrono>
#include <thread>

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
            virtual void SetLevels(DMXData data) = 0;
    };
}