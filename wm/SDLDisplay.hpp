#include "Display.hpp"
#include <string>

namespace beans {
    class SDLDisplay : public Display {
        public:
            SDLDisplay(std::string title);
            ~SDLDisplay();
    };
}