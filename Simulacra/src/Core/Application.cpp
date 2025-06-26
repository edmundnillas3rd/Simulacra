#include "Application.h"

#include "Logger.h"
#include "Window.h"
#include "FileManager.h"

#include "../Platform/OpenGL/OpenGLShader.h"

namespace Simulacra
{
    bool Application::CreateApplication(const std::string& title, uint32_t width, uint32_t height) 
    {
        Title = title;
        Width = width;
        Height = height;
        Running = true;

        return true;
    }

    void Application::RunApplication()
    {
        StartApplicationSubsystems();

        OnStart();

        while (Running)
        {
            PollWindowEvents();

            OnUpdate(0.5f);

            UpdateWindow();
        }

        ShutdownApplicationSubsystems();
    }

    void Application::StartApplicationSubsystems()
    {
        StartLoggerSubsystem();
        StartWindowSubsystem({ Title.c_str(), Width, Height, std::bind(&Application::WindowCallbackfn, this, std::placeholders::_1) });
        StartFileSubsystem();
    }

    void Application::ShutdownApplicationSubsystems()
    {
        ShutdownWindowSubsystem();
        ShutdownLoggerSubsystem();
    }

    void Application::WindowCallbackfn(Event event)
    {
        if (event.Type == EventType::WINDOW_CLOSE)
        {
            Running = false;
        }
    }

}
