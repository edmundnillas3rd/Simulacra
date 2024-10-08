#pragma once

#include <Simulacra.h>

struct Player
{
    glm::vec3 Pos;
};

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
    Simulacra::OrthographicCamera m_Camera;
    Simulacra::Texture m_ContainerTexture;
    Simulacra::Texture m_WallTexture;
    Simulacra::Texture m_FaceTexture;
    Player m_Player;
};