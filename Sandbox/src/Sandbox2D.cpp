#include "Sandbox2D.h"

#include <glad/glad.h>
#include <imgui.H>

Sandbox2D::Sandbox2D()
    : m_Show(false)
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    m_Texture = Simulacra::LoadTexture("assets/images/container.jpg");
    m_AnotherTexture = Simulacra::LoadTexture("assets/images/wall.jpg");
    std::cout << "Layer Attached" << std::endl;
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_0))
    {
        Simulacra::DrawSprite(m_AnotherTexture, glm::vec2(0.0f, 0.0f));
    }
    else if  (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_1))
    {
        Simulacra::DrawSprite(m_Texture, glm::vec2(0.0f, 0.0f));
    }
}

void Sandbox2D::OnImGuiRender()
{
    if (m_Show)
    {
        ImGui::ShowDemoWindow(&m_Show);
    }
}

void Sandbox2D::OnEvent(Simulacra::Event& event)
{
    if (event.Type() == Simulacra::EventType::KEY_RELEASED)
    {
        const auto key = dynamic_cast<Simulacra::KeyPressedUpEvent*>(&event);
        switch (key->KeyCode())
        {
            case Simulacra::VKEY::KEYCODE_BACKQUOTE:
                {
                    m_Show = !m_Show;
                }
            case Simulacra::VKEY::KEYCODE_w:
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                break;
        }
    }
}
