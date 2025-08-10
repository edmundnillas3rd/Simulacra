#include "Application.h"

#include "Logger.h"
#include "Threads.h"

#include "../Renderer/RendererAPI.h"
#include "../Platform/FileSystem.h"
#include "../Platform/OpenGL/OpenGLShader.h"
#include "../Platform/Window.h"

namespace Simulacra
{
    bool Application::Create(const std::optional<Config>& config)
    {
        if (!config.has_value())
            return false;

        m_Config    = config.value();
        m_Running   = true;

        return true;
    }

    void Application::Run()
    {
        StartSubsystems();

        OnStart();

        while (m_Running)
        {
            if (!m_Minimize)
            {
                PollWindowEvents();

                OnUpdate(0.5f);

                ImGuiBeginRender();
                    OnImGuiRender();
                ImGuiEndRender();

                UpdateWindow();
            }
        }

        ShutdownSubsystems();
    }

    void Application::StartSubsystems()
    {
        StartLoggerSubsystem();
        StartThreadsSubsystem();
        StartWindowSubsystem({ m_Config.Title.c_str(), m_Config.Width, m_Config.Height, std::bind(&Application::WindowCallbackfn, this, std::placeholders::_1) });
        StartFileSubsystem(m_Config.WorkingDirectory);
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
        m_Minimize = false;

        if (event.Type == EventType::WINDOW_MINIMIZE)
        {
            m_Minimize = true;
        }

        if (event.Type == EventType::WINDOW_CLOSE)
        {
            m_Running = false;
            return;
        }

        OnEvent(event);
    }

}
