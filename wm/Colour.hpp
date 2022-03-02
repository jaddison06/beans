#pragma once

namespace beans {
    struct Colour {
        int r, g, b;
        int a = 255;
    };

    namespace Colours {
        inline Colour red   = { 255, 0, 0 };
        inline Colour green = { 0, 255, 0 };
        inline Colour blue  = { 0, 0, 255 };

        inline Colour cyan    = { 0, 255, 255 };
        inline Colour magenta = { 255, 0, 255 };
        inline Colour yellow  = { 255, 255, 0 };

        inline Colour black = { 0, 0, 0 };
        inline Colour white = { 255, 255, 255};
    }
}