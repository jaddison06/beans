#pragma once

#include "Display.hpp"
#include "Event.hpp"
#include "BeansUI.hpp"

namespace beans {
    class BeansWindow {
        public:
            BeansWindow();
            ~BeansWindow();

            void Start();

            bool quit = false;

        private:
            Display* display;
            PlatformEvent* platformEvent;

            BeansUI* ui;
            
            int frameCount = 0;
    };
};