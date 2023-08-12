#include "SDL2.h"

#include <glad/glad.h>

#include "Log.h"

namespace Simulacra 
{
    struct SDLProps
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_GLContext context;
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

        SDL_GL_LoadLibrary(nullptr);

        SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        uint32_t windowFlags = 0;
        windowFlags |= SDL_WINDOW_SHOWN;
        windowFlags |= SDL_WINDOW_RESIZABLE;
        windowFlags |= SDL_WINDOW_OPENGL;
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

        s_SDLProps.context = SDL_GL_CreateContext(s_SDLProps.window);
        SDL_GL_MakeCurrent(s_SDLProps.window, s_SDLProps.context);

        gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress);

        SIM_LOG_INFO(
            "\n"
            "Vendor: {}\n"
            "Renderer: {}\n"
            "Version: {}\n",
            reinterpret_cast<const char*>(glGetString(GL_VENDOR)),
            reinterpret_cast<const char*>(glGetString(GL_RENDERER)),
            reinterpret_cast<const char*>(glGetString(GL_VERSION))
        );
        
        uint32_t rendererFlags = 0;
        rendererFlags |= SDL_RENDERER_ACCELERATED;
        rendererFlags |= SDL_RENDERER_PRESENTVSYNC;
        s_SDLProps.renderer = SDL_CreateRenderer(s_SDLProps.window, -1, rendererFlags);

        if (!s_SDLProps.renderer)
        {
            return false;
        }

        SDL_GL_SetSwapInterval(1);

        int w, h;
        SDL_GetWindowSize(s_SDLProps.window, &w, &h);
        glViewport(0, 0, w, h);

        return true;
    }

    void ClearSDLWindowBuffer()
    {
        glClearColor(0.0f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(s_SDLProps.window);
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
        SDL_GL_DeleteContext(s_SDLProps.context);
        SDL_DestroyRenderer(s_SDLProps.renderer);
        SDL_DestroyWindow(s_SDLProps.window);
        SDL_Quit();
    }
}