#include "Sandbox2D.h"

#include <Simulacra.h>

class Sandbox : public Simulacra::Application
{
public:
    Sandbox()
    {
        AddLayer(new Sandbox2D());
    }

    ~Sandbox()
    {
    }
};

Simulacra::Application* Simulacra::CreateApplication()
{
    Simulacra::Application* app = new Sandbox();

    app->Props.Title = "Simulacra";
    app->Props.Width = 1280;
    app->Props.Height = 680;
    app->Props.Path = "../../Sandbox";

    std::cout << "Application Created" << std::endl;

    return app;
}