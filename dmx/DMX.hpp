#pragma once

#include <stdint.h>

namespace beans {
    typedef uint8_t UniverseData[512];

    // A DMXInterface is responsible for a SINGLE UNIVERSE of DMX data
    class DMXInterface {
        virtual bool Send(UniverseData data) = 0;
    };
}