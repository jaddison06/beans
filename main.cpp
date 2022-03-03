#include "wm/WindowManager.hpp"
#include "wm/Display.hpp"
#include "wm/Event.hpp"
#include "wm/V2.hpp"

using namespace beans;

static V2 mouse = { 50, 50 };

void onEvent(WindowManager* wm, Event* event) {
    if (event->type == EventType::Key && event->key == Key::Escape) {
        wm->quit = true;
        return;
    } else if (event->type == EventType::MouseMove) {
        mouse = event->pos;
    }
}

void draw(WindowManager* wm, Display* display) {
    display->FillCircle(mouse, 30, Colours::yellow);
}

int main(int argc, char** argv) {
    auto wm = new WindowManager(draw, onEvent);
    wm->Start();
    delete wm;

    return 0;
}