#include <Simulacra.h>
#include <src/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Simulacra::Layer
{
public:
    Sandbox()
    {
        Simulacra::PushLayer(new Sandbox2D());
    }

    ~Sandbox()
    {

    }
};

Simulacra::Layer* CreateApplication()
{
    return new Sandbox();
}