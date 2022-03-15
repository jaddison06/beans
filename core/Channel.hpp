#pragma once

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include "FixtureData.hpp"
#include "../DMX/DMXInterface.hpp"

namespace beans {
    // Relevant info about a parameter plus its real-time level.
    // See also Parameter, which provides extra DMX metadata.
    struct ChannelParameter {
        int min, max, home, level;
    };

    // maps param name to real value
    typedef std::map<std::string, ChannelParameter*> ChannelData;
    
    class Channel {
        public:
            Channel(FixtureData fixture);
            ~Channel();

            FixtureData fixture;

            ChannelData GetLevels();
            void SetLevels(ChannelData newLevels);

            DMXData GetDmx();

        private:
            ChannelData levels;

            DMXData dmxData;

            void UpdateDmxData();
    };
}