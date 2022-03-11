#pragma once

#include "Channel.hpp"

namespace beans {
    class ChannelProcessor {
        public:
            virtual ChannelData process(ChannelData old) = 0;
    };
}