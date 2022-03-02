#include "wm/SDLDisplay.hpp"
#include <stdio.h>

int main(int argc, char** argv) {
    auto display = beans::SDLDisplay("Test");

    if (display.errorCode != beans::SDLInitErrorCode::Success) {
        printf("%i");
        return 1;
    }

    auto event = new SDL_Event;
    auto quit = false;

    while (!quit) {
        while (SDL_PollEvent(event) > 0) {
            if (event->type == SDL_QUIT) {
                quit = true;
                break;
            } else if (event->type == SDL_KEYDOWN && event->key.keysym.sym == SDLK_ESCAPE) {
                quit = true;
                break;
            }
        }
        display.FillCircle({ 50, 50 }, 30, beans::Colours::yellow);
        display.Flush();
    }

    delete event;

    return 0;
}