#pragma once

#include "Display.hpp"
#include "Event.hpp"
#include "UI.hpp"

namespace beans {
    class Window {
        public:
            Window();
            ~Window();

            void Start();

            bool quit = false;

        private:
            Display* display;
            PlatformEvent* platformEvent;

            UI* ui;
            
            int frameCount = 0;
    };
};