#include "SDL2.h"

namespace Simulacra 
{
    struct SDLProps
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    };

    static SDLProps s_SDLProps;
    bool InitializeSDL(const std::string& title, const uint32_t width, const uint32_t height)
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
            title.c_str(),
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            width,
            height,
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
        SDL_RenderClear(s_SDLProps.renderer);
        SDL_SetRenderDrawColor(s_SDLProps.renderer, 125, 100, 75, SDL_ALPHA_OPAQUE);
        SDL_RenderPresent(s_SDLProps.renderer);
    }

    void PollSDLEvents(const std::function<void(Event)>& fn)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                fn(Event::SIMULACRA_EXIT);
                break;
            case SDL_WINDOWEVENT:
                fn(Event::SIMULACRA_WINDOW_EVENT);
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