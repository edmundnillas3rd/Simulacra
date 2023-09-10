#include "Application.h"

#include <SDL2/SDL.h>
#include <imgui.h>

#include "Event.h"
#include "Window.h"
#include "Log.h"
#include "Layer.h"

#include "src/ImGui/ImGui.h"

namespace Simulacra
{
    struct ApplicationState
    {
        Application* instance;
        bool running;
        
        Window window;
        Event event;
        
        std::vector<std::unique_ptr<Layer>> layerStack;
    };


    static ApplicationState s_State;

    static void StartApplication();
    static void ShutdownApplication();
    static void PollEvents();

    auto callbackFn = [](Event event) -> void {

        s_State.event = event;

        switch (event)
        {
        case Event::SIMULACRA_EXIT:
            s_State.running = false;
            break;
        default:
            break;
        }
    };

    void RunApplication(Application* app)
    {
        s_State.window = CreateWindow(app->name, 1280, 768, callbackFn);

        if (s_State.window.platform == Window::Platform::NONE)
        {
            return;
        }

        s_State.instance = app;

        SIM_LOG_INFO("Application Name: {}", app->name);

        StartApplication();

        float previousFrame = 0.0f;

        while (s_State.running)
        {
            float deltaTime = ((float)SDL_GetTicks64() / 1000.0f) - previousFrame;
            previousFrame = (float)SDL_GetTicks64() / 1000.0f;

            PollEvents();

            {
                for (const auto& layer : s_State.layerStack)
                    layer->OnEvent(s_State.event);
            }

            if (!s_State.running) break;

            {
                for (const auto& layer : s_State.layerStack)
                    layer->OnUpdate(deltaTime);
            }

            ImGuiBegin();
            {
                bool showDemo = true;
                ImGui::ShowDemoWindow(&showDemo);
                
                for (const auto& layer : s_State.layerStack)
                    layer->OnRender();
            }
            ImGuiEnd();

            ClearWindowBuffer(s_State.window);

        }

        ShutdownApplication();
    }

    void PushLayer(Layer* layer)
    {
        s_State.layerStack.emplace_back(layer);
    }

    void PopLayer()
    {
        s_State.layerStack.pop_back();
    }

    static void StartApplication()
    {
        bool success = StartWindow(s_State.instance->path.c_str(), s_State.window);

        if (success)
        {
            s_State.running = true;
        }

        s_State.instance->submit();
    }

    static void PollEvents()
    {
        PollWindowEvents(s_State.window);
    }

    static void ShutdownApplication()
    {
        ShutdownWindow(s_State.window);
    }
}