#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Application
{
public:
    Sandbox2D();
    ~Sandbox2D();

    void OnAttach();
    void OnDetach();
    void OnUpdate(float deltaTime);
    void OnImGuiRender();
    void OnEvent(Simulacra::Event& event);
};