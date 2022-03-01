#pragma once

#include "Display.hpp"
#include <string>
#include <SDL2/SDL.h>

namespace beans {
    enum class SDLInitErrorCode {
        Success,
        InitVideo_Fail,
        CreateWindow_Fail,
        CreateRenderer_Fail
    };

    class SDLDisplay : public Display {
        public:
            SDLDisplay(std::string title, bool fullscreen = true);
            ~SDLDisplay();

            SDLInitErrorCode errorCode;

            V2 GetSize();
            
            void Flush();

            void SetClip(V2 pos, V2 size);
            void ResetClip();

            void DrawPoint(V2 pos, Colour col);
            void DrawLine(V2 a, V2 b, beans::Colour col);
            void DrawRect(V2 pos, V2 size, Colour col);
            void FillRect(V2 pos, V2 size, Colour col);
            void DrawCircle(V2 pos, int radius, Colour col);
            void FillCircle(V2 pos, int radius, Colour col);
        
        private:
            SDL_Window* window;
            SDL_Renderer* renderer;

            void LogSDLError(SDLInitErrorCode errorCode);
            void SetColour(Colour col);
    };
}