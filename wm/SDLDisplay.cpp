//~ link SDL2

#include "SDLDisplay.hpp"

using namespace beans;

SDLDisplay::SDLDisplay(std::string title, bool fullscreen) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LogSDLError(SDLInitErrorCode::InitVideo_Fail);
        return;
    }
    
    window = SDL_CreateWindow(title.c_str(), 40, 40, 350, 350, (fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : SDL_WINDOW_RESIZABLE));

    if (window == NULL) {
        LogSDLError(SDLInitErrorCode::CreateWindow_Fail);
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL) {
        LogSDLError(SDLInitErrorCode::CreateRenderer_Fail);
        return;
    }

    SDL_StartTextInput();

    errorCode = SDLInitErrorCode::Success;   

#undef err        
}

void SDLDisplay::LogSDLError(SDLInitErrorCode errorCode) {
    printf("SDL error: %s\n", SDL_GetError());
    if (window != NULL)
        SDL_DestroyWindow(window);

    if (renderer != NULL)
        SDL_DestroyRenderer(renderer);
    
    SDL_Quit();

    this->errorCode = errorCode;
}

SDLDisplay::~SDLDisplay() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void SDLDisplay::SetClip(V2 pos, V2 size) {
    SDL_Rect clip = { pos.x, pos.y, size.x, size.y };
    SDL_RenderSetClipRect(renderer, &clip);
}

void SDLDisplay::ResetClip() {
    SDL_RenderSetClipRect(renderer, NULL);
}

void SDLDisplay::SetColour(Colour colour) {
    SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
}

V2 SDLDisplay::GetSize() {
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    return { w, h };
}

void SDLDisplay::Flush() {
    SDL_RenderPresent(renderer);
    SetColour(Colours::black);
    SDL_RenderClear(renderer);
}

void SDLDisplay::DrawPoint(V2 pos, Colour colour) {
    SetColour(colour);
    SDL_RenderDrawPoint(renderer, pos.x, pos.y);
}

void SDLDisplay::DrawLine(V2 a, V2 b, Colour colour) {
    SetColour(colour);
    SDL_RenderDrawLine(renderer, a.x, a.y, b.x, b.y);
}

void SDLDisplay::DrawRect(V2 pos, V2 size, Colour colour) {
    SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
    SetColour(colour);
    SDL_RenderDrawRect(renderer, &rect);
}

void SDLDisplay::FillRect(V2 pos, V2 size, Colour colour) {
    SDL_Rect rect = { pos.x, pos.y, size.x, size.y };
    SetColour(colour);
    SDL_RenderFillRect(renderer, &rect);
}

// DrawCircle and FillCircle adapted from https://gist.github.com/Gumichan01/332c26f6197a432db91cc4327fcabb1c
void SDLDisplay::DrawCircle(V2 pos, int radius, Colour colour) {
    SetColour(colour);
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius -1;

    while (offsety >= offsetx) {
        SDL_RenderDrawPoint(renderer, pos.x + offsetx, pos.y + offsety);
        SDL_RenderDrawPoint(renderer, pos.x + offsety, pos.y + offsetx);
        SDL_RenderDrawPoint(renderer, pos.x - offsetx, pos.y + offsety);
        SDL_RenderDrawPoint(renderer, pos.x - offsety, pos.y + offsetx);
        SDL_RenderDrawPoint(renderer, pos.x + offsetx, pos.y - offsety);
        SDL_RenderDrawPoint(renderer, pos.x + offsety, pos.y - offsetx);
        SDL_RenderDrawPoint(renderer, pos.x - offsetx, pos.y - offsety);
        SDL_RenderDrawPoint(renderer, pos.x - offsety, pos.y - offsetx);

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}

void SDLDisplay::FillCircle(V2 pos, int radius, Colour colour) {
    SetColour(colour);
    int offsetx, offsety, d;

    offsetx = 0;
    offsety = radius;
    d = radius -1;

    while (offsety >= offsetx) {
        SDL_RenderDrawLine(renderer, pos.x - offsety, pos.y + offsetx, pos.x + offsety, pos.y + offsetx);
        SDL_RenderDrawLine(renderer, pos.x - offsetx, pos.y + offsety, pos.x + offsetx, pos.y + offsety);
        SDL_RenderDrawLine(renderer, pos.x - offsetx, pos.y - offsety, pos.x + offsetx, pos.y - offsety);
        SDL_RenderDrawLine(renderer, pos.x - offsety, pos.y - offsetx, pos.x + offsety, pos.y - offsetx);

        if (d >= 2*offsetx) {
            d -= 2*offsetx + 1;
            offsetx +=1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }
}