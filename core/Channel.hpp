#pragma once

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include "FixtureData.hpp"

namespace beans {
    union LevelData {
        uint8_t as8bit;
        uint16_t as16bit;
    };

    typedef std::map<std::string, LevelData> ChannelData;

    struct ChannelDmxData {
        int* data;
        int length;
    };

    class Channel {
        public:
            Channel(FixtureData fixture);
            ~Channel();

            FixtureData fixture;
            ChannelData levels;

            ChannelDmxData ToDmx();

        private:
            int addr_count;
            int* dmx_data;
    };
}