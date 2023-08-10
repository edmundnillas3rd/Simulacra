#include <Simulacra.h>
#include <src/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Simulacra::Application
{
public:
    Sandbox(Simulacra::ApplicationArgs args)
        : Simulacra::Application(args)
    {
        Simulacra::PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {

    }
};

Simulacra::Application* CreateApplication()
{
    Simulacra::ApplicationArgs args;
    args.name = "This is a new game title";
    return new Sandbox(args);
}