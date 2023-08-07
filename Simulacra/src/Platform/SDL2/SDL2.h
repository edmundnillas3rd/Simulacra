#pragma once
#include <string>
#include <SDL2/SDL.h>

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

    bool InitializeSDL();
    void PollSDLEvents();
    void ClearSDLWindowBuffer();
    void ShutdownSDL();
}