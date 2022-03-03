#pragma once

#include "Display.hpp"
#include "Event.hpp"

namespace beans {
    class WindowManager;

    typedef void (*DrawCallback)(WindowManager*, Display*);
    typedef void (*EventCallback)(WindowManager*, Event*);

    class WindowManager {
        public:
            WindowManager(DrawCallback draw, EventCallback event);
            ~WindowManager();

            DrawCallback drawCB;
            EventCallback eventCB;

            void Start();

            bool quit = false;

        private:
            Display* display;
            PlatformEvent* platformEvent;
    };
};