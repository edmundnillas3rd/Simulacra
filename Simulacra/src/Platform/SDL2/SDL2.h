#pragma once
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include "src/Event.h"

namespace Simulacra
{
    struct SDLProps
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        std::string title;
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
    };

    bool InitializeSDL(const std::string& title, const uint32_t width, const uint32_t height);
    void PollSDLEvents(const std::function<void(Event)>& fn);
    void ClearSDLWindowBuffer();
    void ShutdownSDL();
}