#include "Sandbox2D.h"

#include <execution>

#include <imgui.h>
#include <glad/glad.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

static uint32_t ConvertToRGBA(const glm::vec4& color)
{
    uint8_t r = (uint8_t)(color.r * 255.0f);
    uint8_t g = (uint8_t)(color.g * 255.0f);
    uint8_t b = (uint8_t)(color.b * 255.0f);
    uint8_t a = (uint8_t)(color.a * 255.0f);

    uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
    return result;
}


Sandbox2D::Sandbox2D()
    : m_Show(false)
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    m_QuadShader = Simulacra::LoadShaders("assets/shaders/default-screen.glsl");
    m_SceneTexture = Simulacra::CreateTexture(200, 100);
    m_HorizontalPixels.resize(m_SceneTexture.Width);
    m_VerticalPixels.resize(m_SceneTexture.Height);

    for (uint32_t i = 0; i < m_HorizontalPixels.size(); i++)
        m_HorizontalPixels[i] = i;
    for (uint32_t i = 0; i < m_VerticalPixels.size(); i++)
        m_VerticalPixels[i] = i;

    m_ImageData = new uint32_t[m_SceneTexture.Width * m_SceneTexture.Height];
    m_DataPtr = new glm::vec4[m_SceneTexture.Width * m_SceneTexture.Height];
}

void Sandbox2D::OnDetach()
{
    delete[] m_ImageData;
    delete[] m_DataPtr;
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    Simulacra::BeginRender();

    // std::for_each(std::execution::par, m_VerticalPixels.begin(), m_VerticalPixels.end(),
    //     [&](uint32_t y) -> void
    //     {
    //         std::for_each(std::execution::par, m_HorizontalPixels.begin(), m_HorizontalPixels.end(),
    //         [&](uint32_t x) -> void
    //         {

    //             glm::vec4 color = PerPixel(x, y);
    //             m_DataPtr[x + y * m_SceneTexture.Width] += color;
    //             glm::vec4 accumulatedColor = m_DataPtr[x + y * m_SceneTexture.Width];
    //             m_ImageData[x + y * m_SceneTexture.Width] = ConvertToRGBA(accumulatedColor);
    //         });
    //     }
    // );

    memset(m_DataPtr, 0, m_SceneTexture.Width * m_SceneTexture.Height * sizeof(glm::vec4));
    for (int j = m_SceneTexture.Height-1; j >= 0; j--)
    {
        for (int i = 0; i < m_SceneTexture.Width; i++)
        {
            glm::vec4 color = PerPixel(i, j);
            m_DataPtr[i + j * m_SceneTexture.Width] += color;
            glm::vec4 accumulatedColor = m_DataPtr[i + j * m_SceneTexture.Width];
            accumulatedColor /= 1.0f;
            m_ImageData[i + j * m_SceneTexture.Width] = ConvertToRGBA(accumulatedColor);
        }
    }

    m_SceneTexture.Data = m_ImageData;
    Simulacra::WritePixel(m_SceneTexture);

    Simulacra::UseShaderProgram(m_QuadShader.ProgramID);
    Simulacra::DrawQuad(m_SceneTexture);
    Simulacra::EndRender();
}

glm::vec4 Sandbox2D::PerPixel(uint32_t x, uint32_t y)
{
    float r = (float)x / (float)m_SceneTexture.Width;
    float g = (float)y / (float)m_SceneTexture.Height;
    float b = 0.2f;

    return glm::vec4(r, g, b, 1.0f);
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
