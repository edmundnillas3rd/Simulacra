#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "Core/Window.h"
#include "Core/Logger.h"

#include "Events/Event.h"
#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"

#include "Platform/OpenGL/OpenGLDebug.h"

namespace Simulacra
{
    static SDL_Window* s_Window;
    static SDL_GLContext s_GLContext;

    struct WindowPointerData
    {
        EventCallbackfn WindowCallbackfn;
    };

    static WindowPointerData s_WindowPointerData;

    static int SDLEventFilter(void* userdata, SDL_Event* event) 
    {
        switch (event->type)
        {
        case SDL_MOUSEBUTTONDOWN:
            {

            }
            break;
        case SDL_MOUSEBUTTONUP:
            {

            }
            break;
        case SDL_KEYDOWN:
            {
                auto* data = (WindowPointerData*)SDL_GetWindowData(s_Window, "WindowData");
                EventType type = EventType::KEY_PRESSED_DOWN;
                Event event = { "Key Down", type };
                data->WindowCallbackfn(event);
            }
            break;
        case SDL_KEYUP:
            {
                auto* data = (WindowPointerData*)SDL_GetWindowData(s_Window, "WindowData");
                EventType type = EventType::KEY_PRESSED_UP;
                Event event = { "Key Up", type };
                data->WindowCallbackfn(event);
            }
            break;
        case SDL_QUIT:
            {
                auto* data = (WindowPointerData*)SDL_GetWindowData(s_Window, "WindowData");
                EventType type = EventType::WINDOW_CLOSE;
                Event event = { "Quit", type };
                data->WindowCallbackfn(event);
            } 
            break;
        }
        return 0;
    }

    void SubmitCallback(const EventCallbackfn& fn)
    {
        s_WindowPointerData.WindowCallbackfn = fn;
    }

    void StartWindowSubsystem(const WindowProps& props)
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
        
        s_Window = SDL_CreateWindow(props.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, props.Width, props.Height, flags);

        if (!s_Window)
            return;

        s_GLContext = SDL_GL_CreateContext(s_Window);
        SDL_GL_MakeCurrent(s_Window, s_GLContext);
        SDL_GL_SetSwapInterval(1);

        if (!s_GLContext)
            return;

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback(glDebugOutput, nullptr);
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
    
        SDL_SetWindowData(s_Window, "WindowData", &s_WindowPointerData);
        SDL_SetEventFilter(SDLEventFilter, nullptr);
    }

    void PollEvents()
    {
        while (SDL_PollEvent(nullptr) != 0);
    }

    void UpdateWindow()
    {
        SDL_GL_SwapWindow(s_Window);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void ShutdownWindowSubsystem()
    {
        SDL_DestroyWindow(s_Window);
    }

    void GetCurrentWindowSize(int& w, int& h)
    {
        SDL_Window* window = SDL_GL_GetCurrentWindow();
        SDL_GetWindowSize(window, &w, &h);
    }
}