#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Layer
{
public:
    Sandbox2D() = default;
    virtual ~Sandbox2D() = default;

    void OnUpdate() override;
    void OnRender() override;
    void OnEvent(Simulacra::Event event) override;
};