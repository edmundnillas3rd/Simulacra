#include "Application.h"

#include <glad/glad.h>

#include "Window.h"


namespace Simulacra
{
    static void StartApplicationSubsystems();
    static void ShutdownApplicationSubsystems();

    struct Application
    {
        WindowProps WinProps;
    };

    static Application s_App;
    static bool s_Running;

    void CreateApplication(const std::string& title, uint32_t width, uint32_t height)
    {
        s_App.WinProps.Title = title;
        s_App.WinProps.Width = width;
        s_App.WinProps.Height = height;

        s_Running = true;
    }

    void RunApplication()
    {
        StartApplicationSubsystems();

        while (s_Running)
        {
            UpdateWindow();
        }

        ShutdownApplicationSubsystems();
    }

    static void StartApplicationSubsystems()
    {
        // StartLoggerSubsystem();
        StartWindowSubsystem(s_App.WinProps);
        // StartRenderingSubsystem();
        // StartFileSubsystem();
    }

    static void ShutdownApplicationSubsystems()
    {

    }
}
