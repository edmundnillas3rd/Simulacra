#include "Application.h"

#include "Logger.h"
#include "WindowManager.h"
#include "Threads.h"

#include "../Renderer/RendererAPI.h"
#include "../Platform/FileSystem.h"
#include "../Platform/OpenGL/OpenGLShader.h"
#include "../Platform/Window.h"

namespace Simulacra
{
    bool Application::Create(const ApplicationConfig& props)
    {
        const auto& [Title, Width, Height, WorkingDirectory] = props;
        m_Props.Title                       = Title;
        m_Props.Width                       = Width;
        m_Props.Height                      = Height;
        m_Props.WorkingDirectory            = WorkingDirectory;
        m_Running                           = true;

        return true;
    }

    void Application::Run()
    {
        StartSubsystems();

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

        ShutdownSubsystems();
    }

    void Application::StartSubsystems()
    {
        StartLoggerSubsystem();
        StartThreadsSubsystem();
        StartWindowSubsystem({ m_Props.Title.c_str(), m_Props.Width, m_Props.Height, std::bind(&Application::WindowCallbackfn, this, std::placeholders::_1) });
        StartFileSubsystem(m_Props.WorkingDirectory);
        StartRendererSubsystem(RendererEngine::OPENGL);
    }

    void Application::ShutdownSubsystems()
    {
        ShutdownRendererSubsystem();
        ShutdownFileSubsystem();
        ShutdownWindowSubsystem();
        ShutdownThreadsSubsystem();
        ShutdownLoggerSubsystem();
    }

    void Application::WindowCallbackfn(Event event)
    {
        if (event.Type == EventType::WINDOW_CLOSE)
        {
            m_Running = false;
            return;
        }

        OnEvent(event);
    }

}
