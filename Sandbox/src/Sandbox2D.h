#pragma once

#include <Simulacra.h>

#include "GameObject.h"

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
private:
    Simulacra::Texture m_ContainerTexture;
    bool m_Show;
    GameObject Player;
};