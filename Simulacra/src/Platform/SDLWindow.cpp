#include "Window.h"

#include <SDL.h>

namespace Simulacra
{
    static SDL_Window* s_Window;

    void CreatePlatformWindow(const char *title, uint32_t width, uint32_t height)
    {
        s_Window = nullptr;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            return;
        }

        s_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

        if (!s_Window)
        {
            return;
        }
    }
}