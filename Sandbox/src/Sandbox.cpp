#include <Simulacra.h>
#include <src/EntryPoint.h>

#include "Sandbox2D.h"

static void Sandbox()
{
    Simulacra::PushLayer(new Sandbox2D());
}

Simulacra::Application* CreateApplication()
{
    Simulacra::Application* args = new Simulacra::Application();
    args->name = "This is a new game title";
    args->submit = Sandbox;
    return args;
}