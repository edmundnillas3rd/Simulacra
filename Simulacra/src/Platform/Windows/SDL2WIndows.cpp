#include "src/Simulacra/Window.h"
#include <iostream>
#include <string>

#include <SDL.h>
#include <glad/glad.h>

#include "src/Events/WindowEvents.h"
#include "src/Simulacra/Window.h"

namespace Simulacra
{
    struct WindowData
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;
        CallbackFn Callback;
    };

    WindowData n_WindowData;

    SDL_Window* s_Window;
    SDL_GLContext s_Context;

    void SubmitApplicationCallback(const CallbackFn& fn)
    {
        n_WindowData.Callback = fn;
    }

    int OnWindowEvent(void* userdata, SDL_Event* event)
    {
        switch(event->type)
        {
        case SDL_KEYDOWN:
            switch (event->key.keysym.sym)
            {
            case SDLK_a:
                std::cout << "Keyboard press a" << std::endl;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event->key.keysym.sym)
            {
            case SDLK_a:
                std::cout << "Keyboard keyup a" << std::endl;
                break;
            }
            break;
        }

        switch (event->type)
        {
        case SDL_QUIT:
            {
                WindowData data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
                WindowCloseEvent wce;
                data.Callback(wce);
            }
            break;
        case SDL_WINDOWEVENT_RESIZED:
            {
                // NOTE(Edmund): temporary approach to resizing viewport
                int w, h;
                SDL_GetWindowSize(s_Window, &w, &h);
                glViewport(0, 0, w, h);

                WindowData data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
                WindowResizeEvent rse(w, h);
                data.Callback(rse);
            }
            break;
        }
        return 0;
    }

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

        n_WindowData.Title = window.Title;
        n_WindowData.Width = window.Width;
        n_WindowData.Height = window.Height;

        SDL_SetWindowData(s_Window, "windowdata", &n_WindowData);
        SDL_AddEventWatch(OnWindowEvent, &n_WindowData);

        std::cout << "Window initialized" << std::endl;

        return true;
    }

    void PollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            SDL_PushEvent(&e);
            // switch(e.type)
            // {
            // case SDL_KEYDOWN:
            //     switch (e.key.keysym.sym)
            //     {
            //     case SDLK_a:
            //         std::cout << "Keyboard press a" << std::endl;
            //         break;
            //     }
            //     break;
            // case SDL_KEYUP:
            //     switch (e.key.keysym.sym)
            //     {
            //     case SDLK_a:
            //         std::cout << "Keyboard keyup a" << std::endl;
            //         break;
            //     }
            //     break;
            // }

            // switch (e.window.event)
            // {
            // case SDL_WINDOWEVENT_CLOSE:
            //     {
            //         WindowCloseEvent wce;
            //         s_WindowDispatcher.Post(wce);
            //     }
            //     break;
            // case SDL_WINDOWEVENT_RESIZED:
            //     {
            //         // NOTE(Edmund): temporary approach to resizing viewport
            //         int w, h;
            //         SDL_GetWindowSize(s_Window, &w, &h);
            //         glViewport(0, 0, w, h);
            //         WindowResizeEvent rse(w, h);
            //         s_WindowDispatcher.Post(rse);
            //     }
            //     break;
            // }
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