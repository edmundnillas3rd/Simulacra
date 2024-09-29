#include "Application.h"

namespace Simulacra
{
    static Application s_App;
    static bool s_Running;

    void CreateApplication(const std::string& title, uint32_t width, uint32_t height)
    {
        s_Running = false;

        s_App.Title = title;
        s_App.Width = width;
        s_App.Height = height;

        if (!s_App.Title.empty())
        {
            s_Running = true;
        }
        else
        {
            // TODO(Edmund): Logged no title, string should not be empty
            return;
        }

        if (s_App.Width > 0 && s_App.Height > 0)
        {
            s_Running = true;
        }
        else
        {
            // TODO(Edmund): Logged no size, always set size > 0
            return;
        }
    }

    void StartApplicationSubsystems()
    {
        // StartWindowSubsystem();
        // StartRenderingSubsystem();
        // StartLoggerSubsystem();
        // StartFileSubsystem();
    }

    void RunApplication()
    {
        StartApplicationSubsystems();

        while (s_Running)
        {
            // UpdateApplication();
            // RenderApplication();
        }
    }

}
