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
        Window window;
        std::string title;
        uint32_t width;
        uint32_t height;
        bool running;
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

    void RunApplication(const char* title, uint32_t width, uint32_t height)
    {
        s_State.title = title;
        s_State.width = width;
        s_State.height = height;

        s_State.window = CreateWindow(title, width, height, callbackFn);

        if (s_State.window.platform == Window::Platform::NONE)
        {
            return;
        }

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
        ShutdownWindow(s_State.window);
    }
}