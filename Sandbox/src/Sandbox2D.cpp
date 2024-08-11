#include "Sandbox2D.h"

#include <execution>
#include <random>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Utils
{
    float GetRandom()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> distrib(0.0f, 1.0f);

        return distrib(gen);
    }
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
    m_SceneTexture = Simulacra::CreateTexture(1200, 800);
    m_HorizontalPixels.resize(m_SceneTexture.Width);
    m_VerticalPixels.resize(m_SceneTexture.Height);

    for (uint32_t i = 0; i < m_HorizontalPixels.size(); i++)
        m_HorizontalPixels[i] = i;
    for (uint32_t i = 0; i < m_VerticalPixels.size(); i++)
        m_VerticalPixels[i] = i;

    m_ImageData = new uint32_t[m_SceneTexture.Width * m_SceneTexture.Height];
    m_DataPtr = new glm::vec4[m_SceneTexture.Width * m_SceneTexture.Height];

    float R = glm::cos(glm::pi<float>() / 4);
    // ObjectSurfaces.resize(5);
    RandomSpheres();
    // ObjectSurfaces[0] = new Sphere(glm::vec3(-R, 0.0f, -1.0f), R,new Lambertian(glm::vec3(0.0f, 0.0f, 1.0f)));
    // ObjectSurfaces[1] = new Sphere(glm::vec3(R, 0.0f, -1.0f), R,new Lambertian(glm::vec3(1.0f, 0.0f, 0.0f)));
    // ObjectSurfaces[0] = new Sphere(glm::vec3(0.0f, 0.0f, -1.0f), 0.5f,new Lambertian(glm::vec3(0.8f, 0.3f, 0.3f)));
    // ObjectSurfaces[1] = new Sphere(glm::vec3(0.0f, -100.5f, -1.0f), 100.0f, new Lambertian(glm::vec3(0.8f, 0.8f, 0.0f)));
    // ObjectSurfaces[2] = new Sphere(glm::vec3(1.0f, 0.0f, -1.0f), 0.5f, new Metal(glm::vec3(0.8f, 0.6f, 0.2f), 0.0f));
    // ObjectSurfaces[3] = new Sphere(glm::vec3(-1.0f, 0.0f, -1.0f), 0.5f, new Dielectric(1.5f));
    // ObjectSurfaces[4] = new Sphere(glm::vec3(-1.0f, 0.0f, -1.0f), -0.45f, new Dielectric(1.5f));
}

void Sandbox2D::OnDetach()
{
    delete[] m_ImageData;
    delete[] m_DataPtr;
}

void Sandbox2D::OnRender()
{
    memset(m_DataPtr, 0, m_SceneTexture.Width * m_SceneTexture.Height * sizeof(glm::vec4));

    std::for_each(std::execution::par, m_VerticalPixels.rbegin(), m_VerticalPixels.rend(), 
        [this](uint32_t y)
        {
            std::for_each(std::execution::par, m_HorizontalPixels.begin(), m_HorizontalPixels.end(), 
                [this, y](uint32_t x)
                {
                    glm::vec4 color = WritePerPixel(x, y);
                    m_DataPtr[x + y * m_SceneTexture.Width] += color;
                    glm::vec4 accumulatedColor = m_DataPtr[x + y * m_SceneTexture.Width];
                    m_ImageData[x + y * m_SceneTexture.Width] = ConvertToRGBA(accumulatedColor);
                }
            );
        }
    );

    m_VerticalPixels.clear();

    Simulacra::WritePixel(m_SceneTexture, m_ImageData);
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    OnRender();
}

glm::vec4 Sandbox2D::WritePerPixel(uint32_t x, uint32_t y)
{

    glm::vec3 lookFrom (13.0f, 2.0f, 3.0f);
    glm::vec3 lookAt(0.0f, 0.0f, 0.0f);
    float distToFocus = 10.0f;
    float aperture = 0.1f;
    Camera m_Camera(lookFrom, lookAt, glm::vec3(0.0f, 1.0f, 0.0f), 20, (float)m_SceneTexture.Width / (float)m_SceneTexture.Height, aperture, distToFocus);

    int ns = 10;
    glm::vec3 col(0.0f, 0.0f, 0.0f);
    for (int s = 0; s < ns; s++)
    {
        float u = (float)(x + Utils::GetRandom()) / (float) m_SceneTexture.Width;
        float v = (float)(y + Utils::GetRandom()) / (float) m_SceneTexture.Height;

        Ray ray = GetCameraRay(m_Camera, u, v);
        glm::vec3 p = RayPointAtParameter(ray, 2.0f);
        col += glm::vec3(CalculateRay(ray, 0));

    }

    col /= (float)ns;
    col = glm::vec3(glm::sqrt(col.r), glm::sqrt(col.g), glm::sqrt(col.b));

    return glm::vec4(col, 1.0f);
}

glm::vec3 Sandbox2D::CalculateRay(const Ray &ray, int depth)
{
    HitRecord rec;
    float MAXFLOAT = std::numeric_limits<float>::max();
    if (TraverseSurfaceObjects(ray, 0.001f, MAXFLOAT, rec))
    {
        Ray scattered;
        glm::vec3 attenuation;
        if (depth < 50 && rec.MaterialPtr->Scatter(ray, rec, attenuation, scattered))
        {
            return attenuation * CalculateRay(scattered, depth + 1);
        }
        else
        {
            return glm::vec3(0.0f, 0.0f, 0.0f);
        }
    }
    else
    {
        glm::vec3 unitDirection = glm::normalize(ray.Direction);
        float t = 0.5f * (unitDirection.y + 1.0f);
        return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
    }

}

uint32_t Sandbox2D::ConvertToRGBA(glm::vec4& color)
{
    uint8_t r = (uint8_t)(color.r * 255.0f);
    uint8_t g = (uint8_t)(color.g * 255.0f);
    uint8_t b = (uint8_t)(color.b * 255.0f);
    uint8_t a = (uint8_t)(color.a * 255.0f);

    uint32_t result = (a << 24) | (b << 16) | (g << 8) | r;
    return result;
}

void Sandbox2D::RandomSpheres()
{
    // int n = 500;
    ObjectSurfaces.push_back(new Sphere(glm::vec3(0.0f, -1000.0f, 0.0f), 1000.0f, new Lambertian(glm::vec3(0.5f, 0.5f, 0.5f))));
    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            float chooseMat = Utils::GetRandom();
            glm::vec3 center(a + 0.9f * Utils::GetRandom(), 0.2f, b + 0.9f * Utils::GetRandom());
            if (glm::length((center - glm::vec3(4.0f, 0.2f, 0.0f))) > 0.9f)
            {
                if (chooseMat < 0.8f)
                {
                    ObjectSurfaces.push_back(new Sphere(center, 0.2f, new Lambertian(glm::vec3(Utils::GetRandom() * Utils::GetRandom(), Utils::GetRandom() * Utils::GetRandom(), Utils::GetRandom() * Utils::GetRandom()))));
                }
                else if (chooseMat < 0.95f)
                {
                    ObjectSurfaces.push_back(new Sphere(center, 0.2f, new Metal(glm::vec3(0.5f * (1 + Utils::GetRandom()), 0.5f * (1 + Utils::GetRandom()), 0.5f * (1 + Utils::GetRandom())), 0.5f * (1 + Utils::GetRandom()))));
                }
                else
                {
                    ObjectSurfaces.push_back(new Sphere(center, 0.2f, new Dielectric(1.5f)));
                }
            }
        }
    }

    ObjectSurfaces.push_back(new Sphere(glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, new Dielectric(1.5f)));
    ObjectSurfaces.push_back(new Sphere(glm::vec3(-4.0f, 1.0f, 0.0f), 1.0f, new Lambertian(glm::vec3(0.4f, 0.2f, 0.1f))));
    ObjectSurfaces.push_back(new Sphere(glm::vec3(4.0f, 1.0f, 0.0f), 1.0f, new Metal(glm::vec3(0.7f, 0.6f, 0.5f), 0.0)));
}

void Sandbox2D::OnImGuiRender()
{
    if (m_Show)
    {
        ImGui::ShowDemoWindow(&m_Show);
    }

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::SetNextWindowSize(ImVec2(io.DisplaySize));
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGuiWindowFlags mainWindowFlags = 0;
    mainWindowFlags |= ImGuiWindowFlags_NoScrollbar;
    mainWindowFlags |= ImGuiWindowFlags_NoScrollWithMouse;
    mainWindowFlags |= ImGuiWindowFlags_NoTitleBar;
    mainWindowFlags |= ImGuiWindowFlags_NoFocusOnAppearing;
    mainWindowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

    ImGui::Begin("Simulacra", nullptr, mainWindowFlags);
        ImGuiWindowFlags viewportWindowFlags = 0;
        viewportWindowFlags |= ImGuiWindowFlags_NoScrollbar;
        viewportWindowFlags |= ImGuiWindowFlags_NoScrollWithMouse;
        viewportWindowFlags |= ImGuiWindowFlags_NoCollapse;

        ImGuiStyle& style = ImGui::GetStyle();
        style = ImGui::GetStyle();
        style.WindowPadding = ImVec2(0.0f, 0.0f);

        ImGui::Begin("Viewport", nullptr, viewportWindowFlags);
            ImVec2 uvMin = ImVec2(0.0f, 1.0f);                 // Bottom-left
            ImVec2 uvMax = ImVec2(1.0f, 0.0f);                 // Top-right
            ImVec2 size = ImGui::GetWindowSize(); 
            ImGui::Image((void*)m_SceneTexture.TextureID, ImVec2(size.x, size.y), uvMin, uvMax);
        ImGui::End();
    ImGui::End();
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
