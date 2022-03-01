#pragma once

namespace beans {
    struct Colour {
        int r, g, b;
        int a = 255;
    };

    namespace Colours {
        Colour red   = { 255, 0, 0 };
        Colour green = { 0, 255, 0 };
        Colour blue  = { 0, 0, 255 };

        Colour cyan    = { 0, 255, 255 };
        Colour magenta = { 255, 0, 255 };
        Colour yellow  = { 255, 255, 0 };

        Colour black = { 0, 0, 0 };
        Colour white = { 255, 255, 255};
    }
}