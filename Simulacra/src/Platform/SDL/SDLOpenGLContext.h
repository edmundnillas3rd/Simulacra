#pragma once

#include <SDL2/SDL.h>

namespace Simulacra
{
    void* CreateGraphicsContext(SDL_Window* window);
    void MakeContextCurrent(SDL_Window* window, SDL_GLContext context);
}