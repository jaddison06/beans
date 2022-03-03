#pragma once

#include "Event.hpp"
#include <SDL2/SDL.h>

namespace beans {
    class SDLEvent : public PlatformEvent {
        public:
            SDLEvent();
            ~SDLEvent();

            int Poll(Event* event);
        private:
            SDL_Event* raw;

            Key TranslateKey();
            MouseButton TranslateMouseButton();
    };
}