#include "src/Simulacra/Window.h"
#include <iostream>
#include <string>

#include <SDL.h>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include "src/Events/WindowEvents.h"
#include "src/Events/InputEvents.h"
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
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
                    KeyPressedDownEvent kpde(static_cast<VKEY>(event->key.keysym.sym));
                    data.Callback(kpde);
                }
                break;
            case SDL_KEYUP:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
                    KeyPressedUpEvent kpde(static_cast<VKEY>(event->key.keysym.sym));
                    data.Callback(kpde);
                }
                break;
        }

        switch (event->window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
                    WindowCloseEvent wce;
                    data.Callback(wce);
                }
                break;
            case SDL_WINDOWEVENT_RESIZED:
                {
                    int w, h;
                    SDL_GetWindowSize(s_Window, &w, &h);
                    glViewport(0, 0, w, h);

                    WindowData& data = *(WindowData*)SDL_GetWindowData(s_Window, "windowdata");
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
        SDL_GL_MakeCurrent(s_Window, s_Context);
        SDL_GL_SetSwapInterval(1);

        if (!s_Context)
        {
            std::cout << "Failed to create an OpenGL context" << std::endl;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        glViewport(0, 0, window.Width, window.Height);

        n_WindowData.Title = window.Title;
        n_WindowData.Width = window.Width;
        n_WindowData.Height = window.Height;

        SDL_SetWindowData(s_Window, "windowdata", &n_WindowData);
        SDL_AddEventWatch(OnWindowEvent, &n_WindowData);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        const char* GLSLVERSION = "#version 460";
        ImGui_ImplSDL2_InitForOpenGL(s_Window, s_Context);
        ImGui_ImplOpenGL3_Init(GLSLVERSION);

        std::cout << "Window initialized" << std::endl;

        return true;
    }

    void PollEvents()
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) == 1)
        {
            ImGui_ImplSDL2_ProcessEvent(&e);
        }
    }

    void BeginImGuiRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void EndImGuiRender()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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