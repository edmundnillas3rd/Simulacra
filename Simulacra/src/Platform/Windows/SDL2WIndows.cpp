#include "src/Simulacra/Window.h"
#include <iostream>
#include <string>

#include <SDL.h>
#include <glad/glad.h>

#include "src/Events/WindowEvents.h"
#include "src/Simulacra/Window.h"

namespace Simulacra
{
    // NOTE(Edmund): There may be an alternative to this, rather
    // than putthing the declaration of a function from a seperate
    // module.
    // Source - Application.cpp
    void OnEventWindowApplication(const Event<WindowEventType>& event);

    Dispatcher<WindowEventType> s_WindowDispatcher;

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

        SDL_GL_LoadLibrary(nullptr);

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
        glViewport(0, 0, window.Width, window.Height);

        s_WindowDispatcher.Subscribe(WindowEventType::WINDOW_CLOSED, OnEventWindowApplication);
        s_WindowDispatcher.Subscribe(WindowEventType::WINDOW_RESIZED, OnEventWindowApplication);

        std::cout << "Window initialized" << std::endl;

        return true;
    }

    void PollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch(e.type)
            {
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym)
                {
                case SDLK_a:
                    std::cout << "Keyboard press a" << std::endl;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (e.key.keysym.sym)
                {
                case SDLK_a:
                    std::cout << "Keyboard keyup a" << std::endl;
                    break;
                }
                break;
            }

            switch (e.window.event)
            {
            case SDL_WINDOWEVENT_CLOSE:
                {
                    WindowCloseEvent wce;
                    s_WindowDispatcher.Post(wce);
                }
                break;
            case SDL_WINDOWEVENT_RESIZED:
                {
                    // NOTE(Edmund): temporary approach to resizing viewport
                    int w, h;
                    SDL_GetWindowSize(s_Window, &w, &h);
                    glViewport(0, 0, w, h);
                    WindowResizeEvent rse(w, h);
                    s_WindowDispatcher.Post(rse);
                }
                break;
            }
        }
    }

    void PlatformRender(Window window)
    {
        SDL_GL_SwapWindow(s_Window);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    Window GetCurrentWindow()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(s_Window, &w, &h);
        const char* title = SDL_GetWindowTitle(s_Window);

        Window window;
        window.Title = title;
        window.Width = w;
        window.Height = h;

        return window;
    }

    bool ShutdownPlatformWindow()
    {
        SDL_DestroyWindow(s_Window);
        s_Window = nullptr;

        return true;
    }
}