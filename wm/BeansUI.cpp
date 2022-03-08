#include "BeansUI.hpp"
#include "Colour.hpp"

using namespace beans;

static V2 mouse = { 50, 50 };

void BeansUI::Draw(Display* display) {
    display->FillCircle(mouse, 30, Colours::yellow);
}

bool BeansUI::OnEvent(Event* event) {
    switch (event->type) {
        case EventType::Key: {
            if (event->key == Key::Escape) {
                return false;
            }
            break;
        }
        case EventType::MouseMove: {
            mouse = event->pos;
            break;
        }
    }
    return true;
}