#include "Win32Window.h"

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "Window.h"
#include "Logger.h"

#include "Platform/OpenGL/OpenGLDebug.h"

namespace Simulacra
{
    static SDL_Window* s_Window;
    static SDL_GLContext s_GLContext;

    void CreatePlatformWindow(const char *title, uint32_t width, uint32_t height)
    {
        s_Window = nullptr;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            ConsoleError("Failed to initialized SDL");
            ConsoleError("SDL ERROR: {}", SDL_GetError());
            return;
        }

        SDL_GL_LoadLibrary(nullptr);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

        int flags = 0;
        flags |= SDL_WINDOW_RESIZABLE;
        flags |= SDL_WINDOW_OPENGL;
        
        s_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

        if (!s_Window)
        {
            ConsoleError("Failed to create window");
            ConsoleError("SDL ERROR: {}", SDL_GetError());
            return;
        }

        s_GLContext = SDL_GL_CreateContext(s_Window);
        SDL_GL_MakeCurrent(s_Window, s_GLContext);
        SDL_GL_SetSwapInterval(1);

        if (!s_GLContext)
        {
            ConsoleError("Failed to create OpenGL Context");
            ConsoleError("SDL ERROR: {}", SDL_GetError());
            return;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    }

    void UpdateWindow()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        SDL_GL_SwapWindow(s_Window);
    }

    void DestroyPlatformWindow()
    {
        SDL_DestroyWindow(s_Window);
    }
}