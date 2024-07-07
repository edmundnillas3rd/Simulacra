#include "SDL2Windows.h"
#include <iostream>
#include <string>

#include <SDL.h>
#include <glad/glad.h>

namespace Simulacra
{
    // NOTE(Edmund): There may be an alternative to this, rather
    // than putthing the declaration of a function from a seperate
    // module.
    // Source - Application.cpp
    void OnEventExitApplication(const Event<WindowEventType>& event);

    Dispatcher<WindowEventType> WindowDispatcher;

    SDL_Window* s_Window;
    SDL_GLContext s_Context;
    bool InitializePlatformWindow(Window window)
    {
        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            std::cout << "Failed to initialized SDL2" << std::endl;
            std::cout << "SDL2 Error Message: " << SDL_GetError() << std::endl;
            return false;
        }

        SDL_GL_LoadLibrary(NULL);

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

        int flags = 0;
        flags |= SDL_WINDOW_RESIZABLE;
        flags |= SDL_WINDOW_OPENGL;

        s_Window = nullptr;
        s_Window = SDL_CreateWindow(window.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.Width, window.Height, flags);

        if (!s_Window)
        {
            std::cout << "Failed to initialize window" << std::endl;;
            std::cout << "SDL2 Error Message: " << SDL_GetError() << std::endl;
            return false;
        }

        s_Context = SDL_GL_CreateContext(s_Window);

        if (!s_Context)
        {
            std::cout << "Failed to create an OpenGL context" << std::endl;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        SDL_GL_SetSwapInterval(1);

        WindowDispatcher.Subscribe(WindowEventType::WINDOW_CLOSED, OnEventExitApplication);

        

        std::cout << "Window initialized" << std::endl;

        return true;
    }

    void PollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                WindowCloseEvent wce;
                WindowDispatcher.Post(wce);
                break;
            }
        }
    }

    void PlatformRender(Window window)
    {
        SDL_GL_SwapWindow(s_Window);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    }


    bool ShutdownPlatformWindow()
    {
        SDL_DestroyWindow(s_Window);
        s_Window = nullptr;

        return true;
    }
}