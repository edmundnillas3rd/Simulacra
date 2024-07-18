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
#include "src/Events/MouseEvents.h"
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

    SDL_Window* n_Window;
    SDL_GLContext n_Context;

    void SubmitApplicationCallback(const CallbackFn& fn)
    {
        n_WindowData.Callback = fn;
    }

    int OnWindowEvent(void* userdata, SDL_Event* event)
    {
        switch(event->type)
        {
            case SDL_MOUSEMOTION:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(n_Window, "windowdata");
                    int x = event->motion.x;
                    int y = event->motion.y;
                    MouseMovedEvent mme(x, y);
                    data.Callback(mme);
                }
                break;
            case SDL_KEYDOWN:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(n_Window, "windowdata");
                    KeyPressedDownEvent kpde(static_cast<VKEY>(event->key.keysym.sym));
                    data.Callback(kpde);
                }
                break;
            case SDL_KEYUP:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(n_Window, "windowdata");
                    KeyPressedUpEvent kpde(static_cast<VKEY>(event->key.keysym.sym));
                    data.Callback(kpde);
                }
                break;
        }

        switch (event->window.event)
        {
            case SDL_WINDOWEVENT_CLOSE:
                {
                    WindowData& data = *(WindowData*)SDL_GetWindowData(n_Window, "windowdata");
                    WindowCloseEvent wce;
                    data.Callback(wce);
                }
                break;
            case SDL_WINDOWEVENT_RESIZED:
                {
                    int w = event->window.data1;
                    int h = event->window.data2;

                    WindowData& data = *(WindowData*)SDL_GetWindowData(n_Window, "windowdata");
                    WindowResizeEvent rse(w, h);
                    data.Callback(rse);
                }
                break;
        }
        return 0;
    }

    bool InitializeWindow(Window window)
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

        n_Window = nullptr;
        n_Window = SDL_CreateWindow(window.Title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window.Width, window.Height, flags);

        if (!n_Window)
        {
            std::cout << "Failed to initialize window" << std::endl;;
            std::cout << "SDL2 Error Message: " << SDL_GetError() << std::endl;
            return false;
        }

        n_Context = SDL_GL_CreateContext(n_Window);
        SDL_GL_MakeCurrent(n_Window, n_Context);
        SDL_GL_SetSwapInterval(1);

        if (!n_Context)
        {
            std::cout << "Failed to create an OpenGL context" << std::endl;
        }

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        n_WindowData.Title = window.Title;
        n_WindowData.Width = window.Width;
        n_WindowData.Height = window.Height;

        SDL_SetWindowData(n_Window, "windowdata", &n_WindowData);
        SDL_AddEventWatch(OnWindowEvent, &n_WindowData);

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

        ImGui::StyleColorsDark();

        const char* GLSLVERSION = "#version 460";
        ImGui_ImplSDL2_InitForOpenGL(n_Window, n_Context);
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

    void SwapBuffer(Window window)
    {
        SDL_GL_SwapWindow(n_Window);
    }

    void ClearWindowBuffer()
    {
        glClearColor(0.4f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    Window GetCurrentWindow()
    {
        int w = 0, h = 0;
        SDL_GetWindowSize(n_Window, &w, &h);
        const char* title = SDL_GetWindowTitle(n_Window);

        Window window;
        window.Title = title;
        window.Width = w;
        window.Height = h;

        return window;
    }

    bool ShutdownWindow()
    {
        SDL_DestroyWindow(n_Window);
        n_Window = nullptr;

        return true;
    }
}