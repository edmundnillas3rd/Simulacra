#include "SDL2.h"

namespace Simulacra 
{
    static SDLProps s_SDLProps;
    bool InitializeSDL()
    {
        uint32_t sdlFlags = 0;
        sdlFlags |= SDL_INIT_VIDEO;
        sdlFlags |= SDL_INIT_AUDIO;
        sdlFlags |= SDL_INIT_TIMER;
        if (SDL_Init(sdlFlags) < 0)
        {
            return false;
        }

        uint32_t windowFlags = 0;
        windowFlags |= SDL_WINDOW_SHOWN;
        windowFlags |= SDL_WINDOW_RESIZABLE;
        s_SDLProps.window = SDL_CreateWindow(
            s_SDLProps.title.c_str(),
            s_SDLProps.x,
            s_SDLProps.y,
            s_SDLProps.width,
            s_SDLProps.height,
            windowFlags
        );

        if (!s_SDLProps.window)
        {
            return false;
        }

        uint32_t rendererFlags = 0;
        rendererFlags |= SDL_RENDERER_ACCELERATED;
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
        s_SDLProps.renderer = SDL_CreateRenderer(s_SDLProps.window, -1, rendererFlags);

        if (!s_SDLProps.renderer)
        {
            return false;
        }

        return true;
    }

    void ClearSDLWindowBuffer()
    {

    }

    void PollSDLEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                break;
            case SDL_WINDOWEVENT:
                break;
            }
        }
    }

    void ShutdownSDL()
    {
        SDL_DestroyRenderer(s_SDLProps.renderer);
        SDL_DestroyWindow(s_SDLProps.window);
        SDL_Quit();
    }
}