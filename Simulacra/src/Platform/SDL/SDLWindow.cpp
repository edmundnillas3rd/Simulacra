#include "SDLWindow.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "../../Core/Window.h"
#include "../../Core/Logger.h"

#include "../../Events/Event.h"
#include "../../Events/KeyEvents.h"
#include "../../Events/MouseEvents.h"

#include "../OpenGL/OpenGLDebug.h"

namespace Simulacra
{
    static SDL_Window* s_Window;
    static SDL_GLContext s_GLContext;

    struct WindowPointerData
    {
        WindowProps::WindowEventCallbackfn WindowCallbackfn;
    };

    static WindowPointerData s_WindowPointerData;

    void CreatePlatformWindow(const WindowProps& props)
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

        s_WindowPointerData.WindowCallbackfn = props.EventCallbackfn;

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
        glViewport(0, 0, props.Width, props.Height);
    
        SDL_SetWindowData(s_Window, "WindowData", &s_WindowPointerData);
        SDL_SetEventFilter([](void* userdata, SDL_Event* event) -> int {
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
            return 1;
        }, nullptr);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(s_Window, s_GLContext);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void SDLPollWindowEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
            ImGui_ImplSDL2_ProcessEvent(&event);
    }

    void SDLImGuiBeginRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void SDLImGuiEndRender()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void SDLUpdateWindow()
    {
        SDL_GL_SwapWindow(s_Window);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void DestroyPlatformWindow()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyWindow(s_Window);
    }
}