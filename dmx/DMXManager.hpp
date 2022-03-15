#pragma once

#include "ComboInterface.hpp"

#define BEANS_MAX_UNIS UINT16_MAX

namespace beans {
    class DMXManager {
        public:
            DMXManager();
            ~DMXManager();

            void Clear();

            // UNIVERSE INDEXING STARTS FROM 1 !!!
            ComboInterface* GetInterface(uint16_t universe);

        private:
            ComboInterface* interfaces[BEANS_MAX_UNIS];
    };
}