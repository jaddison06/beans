#include "SDLEvent.hpp"

#include <string.h>

//~ link SDL2

using namespace beans;

SDLEvent::SDLEvent() {
    raw = new SDL_Event;
}

SDLEvent::~SDLEvent() {
    delete raw;
}

int SDLEvent::Poll(Event* event) {
    auto out = SDL_PollEvent(raw);
    
    switch (raw->type) {
        case SDL_QUIT: {
            event->type = EventType::Quit;
            break;
        }
        case SDL_KEYDOWN: {
            event->type = EventType::Key;
            event->key = TranslateKey();
            break;
        }
        case SDL_TEXTINPUT: {
            event->type = EventType::Text;
            strcpy(event->text, raw->text.text);
            break;
        }
        case SDL_MOUSEMOTION: {
            event->type = EventType::MouseMove;
            event->pos = { raw->motion.x, raw->motion.y };
            break;
        }
        case SDL_MOUSEBUTTONDOWN: {
            event->type = EventType::MouseDown;
            event->pos = { raw->button.x, raw->button.y };
            event->mouseButton = TranslateMouseButton();
            break;
        }
        case SDL_MOUSEBUTTONUP: {
            event->type = EventType::MouseUp;
            event->pos = { raw->button.x, raw->button.y };
            event->mouseButton = TranslateMouseButton();
            break;
        }
        
        default: {
            event->type = EventType::None;
            break;
        }
    }

    return out;
}

Key SDLEvent::TranslateKey() {
    switch (raw->key.keysym.sym) {
        case SDLK_RETURN:    return Key::Return;
        case SDLK_ESCAPE:    return Key::Escape;
        case SDLK_BACKSPACE: return Key::Backspace;
        case SDLK_DELETE:    return Key::Delete;
        case SDLK_TAB:       return Key::Tab;

        case SDLK_INSERT:   return Key::Insert;
        case SDLK_HOME:     return Key::Home;
        case SDLK_END:      return Key::End;
        case SDLK_PAGEUP:   return Key::PageUp;
        case SDLK_PAGEDOWN: return Key::PageDown;

        case SDLK_RIGHT: return Key::ArrowRight;
        case SDLK_LEFT:  return Key::ArrowLeft;
        case SDLK_DOWN:  return Key::ArrowDown;
        case SDLK_UP:    return Key::ArrowUp;

        case SDLK_LCTRL:  return Key::LControl;
        case SDLK_RCTRL:  return Key::RControl;
        case SDLK_LSHIFT: return Key::LShift;
        case SDLK_RSHIFT: return Key::RShift;
        case SDLK_LALT:   return Key::LAlt;
        case SDLK_RALT:   return Key::RAlt;
        
        default: return Key::Unknown;
    }
}

MouseButton SDLEvent::TranslateMouseButton() {
    switch (raw->button.button) {
        case SDL_BUTTON_LEFT:   return MouseButton::Left;
        case SDL_BUTTON_MIDDLE: return MouseButton::Middle;
        case SDL_BUTTON_RIGHT:  return MouseButton::Right;
        default:                return MouseButton::Unknown;
    }
}