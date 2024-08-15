#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    m_Player.Pos = glm::vec3(0.0f, 1.0f, 1.0f);
    m_ContainerTexture = Simulacra::LoadTexture("assets/images/container.jpg");
    m_FaceTexture = Simulacra::LoadTexture("assets/images/awesomeface.png");

    auto window = Simulacra::GetCurrentWindow();
    Simulacra::OrthographicCamera camera(0.0f, window.Width, window.Height, 0.0f);
    m_Camera = camera;
    Simulacra::SetOrthoCameraPosition(m_Camera, glm::vec3(0.0f, 0.0f, 0.0f));
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    Simulacra::BeginRender(m_Camera);

    float speed = 360.0f;
    if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_A))
    {
        m_Player.Pos.x -= speed * deltaTime;
    }
    else if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_D))
    {
        m_Player.Pos.x += speed * deltaTime;
    }

    if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_W))
    {
        m_Player.Pos.y -= speed * deltaTime;
    }
    else if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_S))
    {
        m_Player.Pos.y += speed * deltaTime;
    }

    Simulacra::SetOrthoCameraPosition(m_Camera, glm::vec3(m_Player.Pos.x, m_Player.Pos.y, 0.0f));
    
    Simulacra::DrawSprite(m_FaceTexture, glm::vec3(640.0f, 320.0f, 0.0f));
    Simulacra::DrawSprite(m_ContainerTexture, glm::vec3(0.0f, 0.0f, 0.0f));
    Simulacra::EndRender();
}

void Sandbox2D::OnImGuiRender()
{
}

void Sandbox2D::OnEvent(Simulacra::Event& event)
{
}
