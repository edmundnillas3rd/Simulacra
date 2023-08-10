#include "Application.h"

#include <string>
#include <SDL2/SDL.h>

#include "Event.h"
#include "Window.h"
#include "Log.h"
#include "Layer.h"

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

    void RunApplication(Application* instance, const char* title)
    {
        s_State.instance = instance;
        s_State.window = CreateWindow(title, 1280, 768, callbackFn);

        if (s_State.window.platform == Window::Platform::NONE)
        {
            return;
        }

        SIM_LOG_INFO("Application Name: {}", title);

        StartApplication();

        for (const auto& layer : s_State.layerStack)
        {
            layer->OnStart();
        }

        while (s_State.running)
        {
            PollEvents();

            for (const auto& layer : s_State.layerStack)
            {
                layer->OnEvent(s_State.event);
            }

            if (!s_State.running) break;

            ClearWindowBuffer(s_State.window);

            for (const auto& layer : s_State.layerStack)
            {
                layer->OnUpdate();
                layer->OnRender();
            }
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
        bool success = StartWindow(s_State.window);

        if (success)
        {
            s_State.running = true;
        }
    }

    static void PollEvents()
    {
        PollWindowEvents(s_State.window);
    }

    static void ShutdownApplication()
    {
        delete s_State.instance;
        ShutdownWindow(s_State.window);
    }
}