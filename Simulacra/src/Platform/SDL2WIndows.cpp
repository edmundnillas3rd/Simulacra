#include "SDL2Windows.h"
#include <iostream>

#include <SDL.h>

namespace Simulacra
{
    SDL_Window* s_Window;
    bool InitializePlatformWindow(Window window)
    {
        int flags = 0;
        flags |= SDL_WINDOW_SHOWN;
        flags |= SDL_WINDOW_OPENGL;

        s_Window = nullptr;
        s_Window = SDL_CreateWindow(window.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.Width, window.Height, flags);

        if (!s_Window)
        {
            std::cout << "Failed to initialize window" << std::endl;;
            std::cout << "SDL2 Error Message: " << SDL_GetError() << std::endl;
            return false;
        }

        std::cout << "Window initialized" << std::endl;

        return true;
    }

    void PlatformEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_QUIT:
                break;
            }
        }
    }


    bool ShutdownPlatformWindow()
    {
        SDL_DestroyWindow(s_Window);
        s_Window = nullptr;

        return true;
    }
}