#pragma once

#include "DataSource.hpp"
#include "ChannelProcessor.hpp"
#include "dmx/DMXInterface.hpp"
#include "dmx/DMXManager.hpp"

#include <vector>

// DATA FLOW IN BEANS:
// A channel can have one DataSource at a time, which gives it initial values.
// Subsequently, it can have a chain of ChannelProcessors, which can modify the levels
// incrementally or change them absolutely.

namespace beans {
    struct EngineChannel {
        uint16_t num;
        uint16_t address;
        Channel* channel;
        DataSource* currentDataSource;
        std::vector<ChannelProcessor*> processors;
    };

    struct Universe {
        uint16_t num;
        std::vector<EngineChannel> channels;
        DMXInterface* iface;
    };

    // The Beans engine processes and updates channel data in real-time.
    // There can be multiple engine instances which the user can switch between.
    class Engine {
        public:
            std::vector<Universe> universes;

            void LoadPatch(std::string dataFile, DMXManager* manager);

            void Tick();
    };
}