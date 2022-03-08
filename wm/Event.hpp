#pragma once

#include "V2.hpp"

namespace beans {
    enum class EventType {
        None,
        Quit,
        Key,
        Text,
        MouseMove,
        MouseDown,
        MouseUp
    };

    enum class Key {
        Return,
        Escape,
        Backspace,
        Delete,
        Tab,

        Insert,
        Home,
        End,
        PageUp,
        PageDown,

        ArrowRight,
        ArrowLeft,
        ArrowDown,
        ArrowUp,

        LControl,
        RControl,
        LShift,
        RShift,
        LAlt,
        RAlt,

        Unknown
    };

    enum class MouseButton {
        Left,
        Middle,
        Right,
        Unknown
    };

    enum Modifier {
        Shift = 1,
        Ctrl = 2,
        Alt = 4,
        //Caps = 8
    };

    struct Event {
        EventType type;
        V2 pos;
        Key key;
        // SDL_Event uses a 32 byte buffer
        char text[32];
        char modifiers = 0;
        MouseButton mouseButton;
    };

    class PlatformEvent {
        public:
            virtual int Poll(Event* event) = 0;
    };
}