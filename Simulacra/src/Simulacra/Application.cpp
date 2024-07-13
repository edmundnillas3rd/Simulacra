#include "Application.h"

#include "src/Events/WindowEvents.h"
#include "Time.h"

namespace Simulacra
{
    Application* CreateApplication();
    Application* App;

    Window s_Window;

    std::vector<Application*> s_Layers;

    void StartApplication();
    void ShutdownApplication();

    void AddLayer(Application* layer)
    {
        s_Layers.push_back(layer);
    }

    std::vector<Application*> QueryLayers()
    {

        if (s_Layers.empty())
        {
            std::cout << "List is empty" << std::endl;
            return s_Layers;
        }
            
        return s_Layers;
    }

    bool OnExitWindow(Event& event)
    {
        App->Running = false;
        return true;
    }

    bool OnResizeWindow(Event& event)
    {
        return true;
    }

    void OnEventWindowApplication(Event& event)
    {
        Dispatcher dispatcher(event);

        dispatcher.Post<WindowCloseEvent>(OnExitWindow);
        dispatcher.Post<WindowCloseEvent>(OnExitWindow);
        for (const auto& layer : s_Layers)
        {
            if (event.IsHandled())
                break;
            layer->OnEvent(event);
        }
    }

    void Run()
    {
        StartApplication();

        float lastFrame = 0.0f;
        while (App->Running)
        {
            float time = CurrentTime() / 1000.0f;
            float deltaTime = time - lastFrame;
            lastFrame = time;

            PollEvents();

            PlatformRender(s_Window);


            for (const auto& layer : QueryLayers())
            {
                layer->OnUpdate(deltaTime);
            }
        }

        ShutdownApplication();
    }

    void StartApplication()
    {
        s_Window = { App->Props.Title, App->Props.Width, App->Props.Height };

        InitializePlatformWindow(s_Window);

        SubmitApplicationCallback(OnEventWindowApplication);

        for (const auto& layer : QueryLayers())
        {
            layer->OnAttach();
        }

        App->Running = true;
    }

    void ShutdownApplication()
    {
        ShutdownPlatformWindow();

        for (const auto& layer : QueryLayers())
        {
            layer->OnDetach();
        }
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