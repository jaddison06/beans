#include "wm/SDLDisplay.hpp"

int main(int argc, char** argv) {
    auto display = beans::SDLDisplay("Test");
    auto event = new SDL_Event;
    auto quit = false;

    while (!quit) {
        while (SDL_PollEvent(event) > 0) {
            if (event->type == SDL_QUIT) {
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