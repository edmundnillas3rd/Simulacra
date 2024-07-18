#include "Application.h"

#include "Time.h"
#include "Filesystem.h"
#include "src/Simulacra/Renderer/Renderer.h"
#include "src/Events/WindowEvents.h"

namespace Simulacra
{
    Application* CreateApplication();
    Application* App;

    Window n_Window;

    std::vector<Application*> n_Layers;

    void StartApplication();
    void ShutdownApplication();

    void AddLayer(Application* layer)
    {
        n_Layers.push_back(layer);
    }

    std::vector<Application*> QueryLayers()
    {

        if (n_Layers.empty())
        {
            std::cout << "List is empty" << std::endl;
            return n_Layers;
        }
            
        return n_Layers;
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
        for (const auto& layer : n_Layers)
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

            BeginImGuiRender();

            for (const auto& layer : QueryLayers())
            {
                layer->OnImGuiRender();
            }

            EndImGuiRender();

            SwapBuffer(n_Window);
            ClearWindowBuffer();

            for (const auto& layer : QueryLayers())
            {
                layer->OnUpdate(deltaTime);
            }

        }

        ShutdownApplication();
    }

    void StartApplication()
    {
        n_Window = { App->Props.Title, App->Props.Width, App->Props.Height, App->Props.Path };

        InitializeWindow(n_Window);
        InitializeFilesystem(n_Window);
        InitializeRenderer();

        SubmitApplicationCallback(OnEventWindowApplication);

        for (const auto& layer : QueryLayers())
        {
            layer->OnAttach();
        }

        App->Running = true;
    }

    void ShutdownApplication()
    {
        for (const auto& layer : QueryLayers())
        {
            layer->OnDetach();
        }

        ShutdownWindow();
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