#include "Application.h"

#ifdef _WIN32
    #include "Platform/SDL2Windows.h"
#else
    #error "Platform not yet supported
#endif

namespace Simulacra
{
    extern Application* CreateApplication();
    Application* App;

    void StartApplication();
    void ShutdownApplication();

    // NOTE(Edmund): Revise this event handling callback
    void OnEventExitApplication(const Event<WindowEventType>& event)
    {
        if (event.Type() == WindowEventType::WINDOW_CLOSED)
            App->Running = false;
    }

    void Run()
    {
        StartApplication();

        while (App->Running)
        {
            PlatformEvents();
        }

        ShutdownApplication();
    }

    void StartApplication()
    {
        Window window = {
            App->Props.Title,
            App->Props.Width,
            App->Props.Height
        };

        InitializePlatformWindow(window);

        App->Running = true;
    }

    void ShutdownApplication()
    {
        ShutdownPlatformWindow();
    }
   
}

int main(int argc, char* argv[])
{
    Simulacra::App = nullptr;
    Simulacra::App = Simulacra::CreateApplication();
    Simulacra::Run();

    delete Simulacra::App;
    Simulacra::App = nullptr;

    return 0;
}