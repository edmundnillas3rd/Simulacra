#include "Application.h"

#include "Logger.h"
#include "Window.h"
#include "FileManager.h"
#include "../Renderer/Renderer2D.h"

#include "../Platform/OpenGL/OpenGLShader.h"

namespace Simulacra
{
    static void StartApplicationSubsystems();
    static void ShutdownApplicationSubsystems();

    struct Application
    {
        WindowProps WinProps;
        std::vector<ApplicationLayer*> Layers;
    };

    static Application s_App;
    static bool s_Running;

    void PushApplicationLayer(ApplicationLayer* layer)
    {
        s_App.Layers.push_back(layer);
    }

    void AppplicationWindowCallbackfn(Event event)
    {
        for (const auto& layer : s_App.Layers)
            layer->OnEvent(event);

        if (event.Type == EventType::WINDOW_CLOSE)
        {
            s_Running = false;
        }
    }

    void CreateApplication(const std::string& title, uint32_t width, uint32_t height) 
    {
        s_App.WinProps.Title = title;
        s_App.WinProps.Width = width;
        s_App.WinProps.Height = height;

        s_Running = true;
        SubmitWindowEventCallback(AppplicationWindowCallbackfn);
    }

    void RunApplication()
    {
        StartApplicationSubsystems();

        for (const auto& layer : s_App.Layers)
            layer->OnStart();

        while (s_Running)
        {
            PollWindowEvents();

            for (const auto& layer : s_App.Layers)
                layer->OnUpdate(0.5f);

            UpdateWindow();
        }

        ShutdownApplicationSubsystems();
    }

    static void StartApplicationSubsystems()
    {
        StartLoggerSubsystem();
        StartWindowSubsystem(s_App.WinProps);
        StartFileSubsystem();
        StartRendererSubsystem();
    }

    static void ShutdownApplicationSubsystems()
    {
        ShutdownWindowSubsystem();
        ShutdownLoggerSubsystem();
    }
}
