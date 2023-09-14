#pragma once
#include <string>
#include <functional>

#include <SDL2/SDL.h>

#include "src/Core/Event.h"

namespace Simulacra
{
    struct SDLWindowProps
    {
        int Width;
        int Height;
    };

    SDL_GLContext GetContext();
    SDL_Window* GetWindow();
    SDLWindowProps GetWindowProps();

    void InitializeSDL(const std::string& title, const uint32_t width, const uint32_t height);
    void PollSDLEvents(const std::function<void(Event, SDL_Event)>& fn);

    void ClearSDLWindowBuffer();
    void ShutdownSDL();
}