#pragma once

#include <stdint.h>

namespace beans {
    typedef uint8_t UniverseData[512];

    // A DMXInterface is responsible for a SINGLE UNIVERSE of DMX data
    // It should start continuously outputting DMX when it's constructed, and finish
    // when it's destroyed.
    class DMXInterface {
        public:
            UniverseData data;
    };

    class DMXManager {
        public:
            DMXInterface* GetInterface(uint16_t universe);
    };
}