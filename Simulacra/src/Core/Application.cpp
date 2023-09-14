#include "Application.h"

#include "Event.h"
#include "Window.h"
#include "Log.h"
#include "Layer.h"

#include "src/ImGui/ImGui.h"

namespace Simulacra
{
    struct ApplicationState
    {
        Application* Instance;
        bool Running;
        
        Window ApplicationWindow;
        Event ApplicationEvent;
        
        std::vector<std::unique_ptr<Layer>> LayerStack;
    };


    static ApplicationState s_State;

    auto callbackFn = [](Event event) -> void {

        // TODO: Find an alternative means of getting the SDL_Events for ImGui
        s_State.ApplicationEvent = event;

        ImGuiEvent(event.APIEvent);

        switch (event.Type)
        {
        case EventType::SIMULACRA_EXIT:
            s_State.Running = false;
            break;
        default:
            break;
        }
    };

    void RunApplication(Application* app)
    {
        s_State.ApplicationWindow = CreateWindow(app->name, 1280, 768, callbackFn);

        s_State.Instance = app;

        SIM_LOG_INFO("Application Name: {}", app->name);

        StartWindow(s_State.Instance->path.c_str(), s_State.ApplicationWindow);
        s_State.Instance->submit();
        s_State.Running = true;

        ImGuiOnAttach();

        float previousFrame = 0.0f;

        while (s_State.Running)
        {
            float deltaTime = ((float)SDL_GetTicks64() / 1000.0f) - previousFrame;
            previousFrame = (float)SDL_GetTicks64() / 1000.0f;

            PollWindowEvents(s_State.ApplicationWindow);

            {
                for (const auto& layer : s_State.LayerStack)
                    layer->OnEvent(s_State.ApplicationEvent);
            }

            if (!s_State.Running) break;

            {
                for (const auto& layer : s_State.LayerStack)
                    layer->OnUpdate(deltaTime);
            }

            ImGuiBegin();
            {
                for (const auto& layer : s_State.LayerStack)
                    layer->OnImGuiRender();
            }
            ImGuiEnd();

            ClearWindowBuffer();

        }

        ImGuiOnDetach();

        ShutdownWindow();

    }

    void PushLayer(Layer* layer)
    {
        s_State.LayerStack.emplace_back(layer);
    }

    void PopLayer()
    {
        s_State.LayerStack.pop_back();
    }
}