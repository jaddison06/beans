#pragma once

#include "Channel.hpp"

namespace beans {
    class DataSource {
        public:
            // dunno how we're gonna identify channels, we'll cross that bridge when we come to it
            virtual ChannelData GetChannelData(Channel* channel) {
                return channel->GetLevels();
            }
    };
}