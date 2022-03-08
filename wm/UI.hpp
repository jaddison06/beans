#pragma once

#include "Display.hpp"
#include "Event.hpp"

namespace beans {
    class UI {
        public:
            void Draw(Display* display);
            bool OnEvent(Event* event);
    };
}