#include <string>

#include <SDL2/SDL.h>

namespace Simulacra
{
    struct ApplicationState
    {
        std::string title;
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
        bool running;
    };

    struct SDLProps
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
    };

    static ApplicationState s_State;
    static SDLProps s_SDLProps;

    static void StartApplication();
    static void ShutdownApplication();
    static void PollEvents();

    void RunApplication(const char* title, uint32_t width, uint32_t height)
    {
        s_State.title = title;
        s_State.x = SDL_WINDOWPOS_UNDEFINED;
        s_State.y = SDL_WINDOWPOS_UNDEFINED;
        s_State.width = width;
        s_State.height = height;

        StartApplication();
        while (s_State.running)
        {
            PollEvents();

            if (!s_State.running) break;
        }
        ShutdownApplication();
    }

    static void StartApplication()
    {
        uint32_t sdlFlags = 0;
        sdlFlags |= SDL_INIT_VIDEO;
        sdlFlags |= SDL_INIT_AUDIO;
        sdlFlags |= SDL_INIT_TIMER;
        if (SDL_Init(sdlFlags) < 0)
        {
        }

        uint32_t windowFlags = 0;
        windowFlags |= SDL_WINDOW_SHOWN;
        windowFlags |= SDL_WINDOW_RESIZABLE;
        s_SDLProps.window = SDL_CreateWindow(
            s_State.title.c_str(),
            s_State.x,
            s_State.y,
            s_State.width,
            s_State.height,
            windowFlags
        );

        uint32_t rendererFlags = 0;
        rendererFlags |= SDL_RENDERER_ACCELERATED;
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
        s_SDLProps.renderer = SDL_CreateRenderer(s_SDLProps.window, -1, rendererFlags);

        s_State.running = true;
    }

    static void PollEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                s_State.running = false;
                break;
            case SDL_WINDOWEVENT:
                break;
            }
        }
    }

    static void ShutdownApplication()
    {
        SDL_DestroyRenderer(s_SDLProps.renderer);
        SDL_DestroyWindow(s_SDLProps.window);
        SDL_Quit();
    }
}