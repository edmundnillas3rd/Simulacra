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

    void InitializeWindow();
    void ShutdownWindow();

    void Run()
    {
        InitializeWindow();
        ShutdownWindow();
    }

    void InitializeWindow()
    {
        Window window = {
            App->props.Title,
            App->props.Width,
            App->props.Height
        };

        InitializePlatformWindow(window);
    }

    void ShutdownWindow()
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