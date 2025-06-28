#include "Application.h"

#include "Logger.h"
#include "Window.h"
#include "FileManager.h"

#include "../Renderer/RendererAPI.h"
#include "../Platform/OpenGL/OpenGLShader.h"

namespace Simulacra
{
    bool Application::CreateApplication(const ApplicationProps& props)
    {
        m_Props.Title = props.Title;
        m_Props.Width = props.Width;
        m_Props.Height = props.Height;
        m_Running = true;

        return true;
    }

    void Application::RunApplication()
    {
        StartApplicationSubsystems();

        OnStart();

        while (m_Running)
        {
            PollWindowEvents();
            OnUpdate(0.5f);

            ImGuiBeginRender();
                OnImGuiRender();
            ImGuiEndRender();

            UpdateWindow();
        }

        ShutdownApplicationSubsystems();
    }

    void Application::StartApplicationSubsystems()
    {
        StartLoggerSubsystem();
        StartWindowSubsystem({ m_Props.Title.c_str(), m_Props.Width, m_Props.Height, std::bind(&Application::WindowCallbackfn, this, std::placeholders::_1) });
        StartFileSubsystem("../../..");
        StartRendererSubsystem(RendererEngine::OPENGL);
    }

    void Application::ShutdownApplicationSubsystems()
    {
        ShutdownRendererSubsystem();
        ShutdownLoggerSubsystem();
        ShutdownWindowSubsystem();
    }

    void Application::WindowCallbackfn(Event event)
    {
        if (event.Type == EventType::WINDOW_CLOSE)
        {
            m_Running = false;
        }
    }

}
