#include "SDL2.h"

#include <glad/glad.h>

#include "src/Core/Log.h"
#include "src/ImGui/ImGui.h"

namespace Simulacra 
{
    struct SDLProps
    {
        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        SDL_GLContext context;
    };

    static SDLProps s_SDLProps;

    SDL_GLContext GetContext()
    {
        return s_SDLProps.context;
    }

    SDL_Window* GetWindow()
    {
        return s_SDLProps.window;
    }

    SDLWindowProps GetWindowProps()
    {
        SDLWindowProps window;

        SDL_GetWindowSize(s_SDLProps.window, &window.Width, &window.Height);

        return window;
    }

    void InitializeSDL(const std::string& title, const uint32_t width, const uint32_t height)
    {
        uint32_t sdlFlags = 0;
        sdlFlags |= SDL_INIT_VIDEO;
        sdlFlags |= SDL_INIT_AUDIO;
        sdlFlags |= SDL_INIT_TIMER;

        SDL_GL_LoadLibrary(nullptr);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
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
        windowFlags |= SDL_WINDOW_ALLOW_HIGHDPI;
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
            return;
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
            return;
        }

        SDL_GL_SetSwapInterval(1);

        int w, h;
        SDL_GetWindowSize(s_SDLProps.window, &w, &h);
        glViewport(0, 0, w, h);

    }

    void ClearSDLWindowBuffer()
    {
        SDL_GL_SwapWindow(s_SDLProps.window);
        glClearColor(0.0f, 0.5f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void PollSDLEvents(const std::function<void(Event)>& fn)
    {
        SDL_Event event;
        Event e;
        while (SDL_PollEvent(&event))
        {
            e.APIEvent = event;
            e.Type = EventType::SIMULACRA_NONE;
            fn(e);
            switch (event.type)
            {
            case SDL_QUIT:
                e.Type = EventType::SIMULACRA_EXIT;
                fn(e);
                break;
            case SDL_WINDOWEVENT:
                e.Type = EventType::SIMULACRA_WINDOW_EVENT;
                fn(e);
                if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    glViewport(0, 0, event.window.data1, event.window.data2);
                    e.Type = EventType::SIMULACRA_WINDOW_RESIZE_EVENT;
                    fn(e);
                }

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