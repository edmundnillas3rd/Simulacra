#include <Simulacra.h>
#include <src/Core/EntryPoint.h>

#include "Sandbox2D.h"

static void Sandbox()
{
    Simulacra::PushLayer(new Sandbox2D());
}

Simulacra::Application* CreateApplication()
{
    Simulacra::Application* app = new Simulacra::Application();
    app->name = "This is a new game title";
    app->path = "../../Sandbox";
    app->submit = Sandbox;
    return app;
}