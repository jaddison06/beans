#pragma once

#include "DMXInterface.hpp"

#define BEANS_MAX_UNIS UINT16_MAX

namespace beans {
    class DMXManager {
        public:
            DMXManager();
            ~DMXManager();
            
            // UNIVERSE INDEXING STARTS FROM 1 !!!
            DMXInterface* GetInterface(uint16_t universe);

        private:
            DMXInterface* interfaces[BEANS_MAX_UNIS];
    };
}