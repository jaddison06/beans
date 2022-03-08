#pragma once

// DATA FLOW IN BEANS:
// A channel can have one DataSource at a time, which gives it initial values.
// Subsequently, it can have a chain of ChannelProcessors, which can modify the levels
// incrementally or change them absolutely.

namespace beans {
    // The Beans engine processes and updates channel data in real-time.
    // There can be multiple engine instances which the user can switch between.
    class Engine {
        
    };
}