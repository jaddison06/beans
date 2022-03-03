#include "WindowManager.hpp"

#include "SDLDisplay.hpp"
#include "SDLEvent.hpp"

using namespace beans;

// todo: abstraction for event poll !!!

WindowManager::WindowManager(DrawCallback draw, EventCallback event) {
    display = new SDLDisplay("beans");
    platformEvent = new SDLEvent();

    this->drawCB = draw;
    this->eventCB = event;
}

WindowManager::~WindowManager() {
    delete platformEvent;
    delete display;
}

void WindowManager::Start() {
    auto event = new Event;

    while (!quit) {
        while (platformEvent->Poll(event) > 0) {
            if (event->type == EventType::Quit) {
                quit = true;
            }
            eventCB(this, event);
        }
        drawCB(this, display);
        display->Flush();
    }

    delete event;
}