#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D();

    void OnUpdate() override;
    void OnRender() override;
    void OnEvent(Simulacra::Event event) override;
};