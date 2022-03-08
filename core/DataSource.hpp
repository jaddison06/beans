#pragma once

#include "Channel.hpp"

namespace beans {
    class DataSource {
        public:
            // return false if the source doesn't know anything about the channel
            virtual bool SetChannelData(Channel* channel);
    };
}