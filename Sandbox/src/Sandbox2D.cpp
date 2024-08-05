#include "Sandbox2D.h"

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : m_Show(false)
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    m_ContainerTexture = Simulacra::LoadTexture("assets/images/container.jpg");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    Simulacra::BeginRender();

    static float x;
    static float y;

    if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_A))
    {
        x += 5.0f * deltaTime;
    }
    else if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_D))
    {
        x -= 5.0f * deltaTime;
    }

    if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_S))
    {
        y += 5.0f * deltaTime;
    }
    else if (Simulacra::IsKeyPressed(Simulacra::SCANCODE::SCANCODE_W))
    {
        y -= 5.0f * deltaTime;
    }

    // Base on trial and error, 8000 quads is the maximum number before the performance slowed down.
    // At least in this particular hardware
    for (size_t i = 0; i < 8000; i++)
        Simulacra::DrawSprite(m_ContainerTexture, glm::vec3({ (float)i + x, y, -1.0f }));

    Simulacra::EndRender();
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
                break;
        }
    }

}
