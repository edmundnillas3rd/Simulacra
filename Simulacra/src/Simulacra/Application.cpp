#include "Application.h"

#ifdef _WIN32
    #include "Platform/SDL2Windows.h"
    #include "Renderer.h"
#else
    #error "Platform not yet supported
#endif

namespace Simulacra
{
    extern Application* CreateApplication();
    Application* App;
    Window window;

    std::vector<Application*> m_Layers;

    void StartApplication();
    void ShutdownApplication();

    void AddLayer(Application* layer)
    {
        m_Layers.push_back(layer);
    }

    std::vector<Application*> QueryLayers()
    {

        if (m_Layers.empty())
        {
            std::cout << "List is empty" << std::endl;
            return m_Layers;
        }
            
        return m_Layers;
    }

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
            PollEvents();

            for (const auto& layer : QueryLayers())
            {
                layer->OnEvent();
            }

            PlatformRender(window);

            for (const auto& layer : QueryLayers())
            {
                layer->OnUpdate(1.05f);
            }
        }

        ShutdownApplication();
    }

    void StartApplication()
    {
        window = {
            App->Props.Title,
            App->Props.Width,
            App->Props.Height
        };

        InitializePlatformWindow(window);
        InitializeRenderer();

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