#pragma once

#include "Display.hpp"
#include "Event.hpp"

namespace beans {
    class BeansUI {
        public:
            void Draw(Display* display);
            bool OnEvent(Event* event);
    };
}