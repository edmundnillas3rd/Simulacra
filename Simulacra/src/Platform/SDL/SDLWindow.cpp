#include "SDLWindow.h"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_sdl2.h>

#include <glad/glad.h>
#include <SDL2/SDL.h>

#include "SDLOpenGLContext.h"

#include "../../Core/Logger.h"

#include "../../Events/KeyEvents.h"
#include "../../Events/MouseEvents.h"

#include "../Window.h"
#include "../PlatformUtils.h"

namespace Simulacra
{
    struct WindowPointerData
    {
        WindowProps::WindowEventCallbackfn WindowCallbackfn = nullptr;
    };

    struct PlatformWindow
    {
        SDL_Window* Window = nullptr;
        SDL_GLContext GLContext = nullptr;
    };

    static WindowPointerData s_WindowPointerData;
    static PlatformWindow s_PlatformWindow;

    void CreatePlatformWindow(const std::string& title, uint32_t width, uint32_t height, const std::function<void(Event)>& eventCallbackfn)
    {
        s_PlatformWindow.Window = nullptr;

        if (SDL_Init(SDL_INIT_VIDEO) < 0)
        {
            SIMULACRA_ERROR("Failed to initialized SDL: {}", SDL_GetError());
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
        
        s_PlatformWindow.Window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

        s_WindowPointerData.WindowCallbackfn = eventCallbackfn;

        s_PlatformWindow.GLContext = CreateGraphicsContext(s_PlatformWindow.Window);
        MakeContextCurrent(s_PlatformWindow.Window, s_PlatformWindow.GLContext);

        SDL_GL_SetSwapInterval(1);

        gladLoadGLLoader(SDL_GL_GetProcAddress);

        glEnable(GL_DEBUG_OUTPUT);
        glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        glDebugMessageCallback([](GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char *message, const void *userParam) {
            if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

            std::string msg;
            msg += "ID: " + std::to_string(id) + " ";
            msg += "Message: " + std::string(message) + " ";

            switch (source)
            {
                case GL_DEBUG_SOURCE_API:                               msg += "Source: API"; break;
                case GL_DEBUG_SOURCE_WINDOW_SYSTEM:                     msg += "Source: Window System"; break;
                case GL_DEBUG_SOURCE_SHADER_COMPILER:                   msg += "Source: Shader Compiler"; break;
                case GL_DEBUG_SOURCE_THIRD_PARTY:                       msg += "Source: Third Party"; break;
                case GL_DEBUG_SOURCE_APPLICATION:                       msg += "Source: Application"; break;
                case GL_DEBUG_SOURCE_OTHER:                             msg += "Source: Other"; break;
            }

            switch (type)
            {
                case GL_DEBUG_TYPE_ERROR:                               msg += "Type: Error"; break;
                case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:                 msg += "Type: Deprecated Behavior"; break;
                case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:                  msg += "Type: Undefined Behavior"; break;
                case GL_DEBUG_TYPE_PORTABILITY:                         msg += "Type: Portability"; break;
                case GL_DEBUG_TYPE_PERFORMANCE:                         msg += "Type: Performance"; break;
                case GL_DEBUG_TYPE_MARKER:                              msg += "Type: Marker"; break;
                case GL_DEBUG_TYPE_PUSH_GROUP:                          msg += "Type: Push Group"; break;
                case GL_DEBUG_TYPE_POP_GROUP:                           msg += "Type: Pop Group"; break;
                case GL_DEBUG_TYPE_OTHER:                               msg += "Type: Other"; break;
            }

            switch (severity)
            {
                case GL_DEBUG_SEVERITY_HIGH:                            SIMULACRA_ERROR("{}Severity: High", msg); break;
                case GL_DEBUG_SEVERITY_MEDIUM:                          SIMULACRA_WARN("{}Severity: Medium", msg); break;
                case GL_DEBUG_SEVERITY_LOW:                             SIMULACRA_DEBUG("{}Severity: Low", msg); break;
                case GL_DEBUG_SEVERITY_NOTIFICATION:                    SIMULACRA_LOG("{}Severity: Notification", msg); break;
            }

        }, nullptr);
    
        glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        glViewport(0, 0, width, height);
    
        SDL_SetWindowData(s_PlatformWindow.Window, "WindowData", &s_WindowPointerData);
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

        ImGui::StyleColorsDark();

        ImGui_ImplSDL2_InitForOpenGL(s_PlatformWindow.Window, s_PlatformWindow.GLContext);
        ImGui_ImplOpenGL3_Init("#version 460");
    }

    void DestroyPlatformWindow()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_DestroyWindow(s_PlatformWindow.Window);
    }

    void PollWindowEvents()
    {
        SDL_Event event;
        while (SDL_PollEvent(&event) != 0)
        {
            ImGui_ImplSDL2_ProcessEvent(&event);
            switch (event.type)
            {
            case SDL_WINDOWEVENT:
                {

                    switch (event.window.event)
                    {
                    case SDL_WINDOWEVENT_MINIMIZED:
                        {
                            auto* data = (WindowPointerData*)SDL_GetWindowData(s_PlatformWindow.Window, "WindowData");
                            EventType type = EventType::WINDOW_MINIMIZE;
                            Event e = { "Minimize", type, static_cast<VKEY>(0) };
                            data->WindowCallbackfn(e);
                        }
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        {
                            auto* data = (WindowPointerData*)SDL_GetWindowData(s_PlatformWindow.Window, "WindowData");
                            EventType type = EventType::WINDOW_INSTANCE_CLOSE;
                            Event e = { "Window Instance Close", type, static_cast<VKEY>(0) };
                            data->WindowCallbackfn(e);
                        }
                        break;
                    }
                }
                break;
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
                    auto* data = (WindowPointerData*)SDL_GetWindowData(s_PlatformWindow.Window, "WindowData");
                    EventType type = EventType::KEY_PRESSED_DOWN;
                    Event e = { "Key Down", type, static_cast<VKEY>(event.key.keysym.scancode) };
                    data->WindowCallbackfn(e);
                }
                break;
            case SDL_KEYUP:
                {
                    auto* data = (WindowPointerData*)SDL_GetWindowData(s_PlatformWindow.Window, "WindowData");
                    EventType type = EventType::KEY_PRESSED_UP;
                    Event e = { "Key Up", type, static_cast<VKEY>(event.key.keysym.scancode) };
                    data->WindowCallbackfn(e);
                }
                break;
            case SDL_QUIT:
                {
                    auto* data = (WindowPointerData*)SDL_GetWindowData(s_PlatformWindow.Window, "WindowData");
                    EventType type = EventType::WINDOW_CLOSE;
                    Event e = { "Quit", type,  static_cast<VKEY>(0) };
                    data->WindowCallbackfn(e);
                } 
                break;
            }
        }
    }

    void ImGuiBeginRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
    }

    void ImGuiEndRender()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void UpdateWindow()
    {
        SDL_GL_SwapWindow(s_PlatformWindow.Window);
        glClear(GL_COLOR_BUFFER_BIT);
    }
}