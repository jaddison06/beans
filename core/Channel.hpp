#pragma once

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include "FixtureData.hpp"

namespace beans {
    // Relevant info about a parameter plus its real-time level.
    // See also Parameter, which provides extra DMX metadata.
    struct ChannelParameter {
        int min, max, home, level;
    };

    // maps param name to real value
    typedef std::map<std::string, ChannelParameter*> ChannelData;

    struct DMXData {
        uint8_t* data;
        uint8_t length;
    };
    
    class Channel {
        public:
            Channel(FixtureData fixture);
            ~Channel();

            FixtureData fixture;

            void SetLevels(ChannelData newLevels);

            DMXData GetDmx();

        private:
            ChannelData levels;

            DMXData dmxData;

            void UpdateDmxData();
    };
}