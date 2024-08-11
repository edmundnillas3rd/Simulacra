#pragma once

#include <Simulacra.h>

#include "Material.h"
#include "Ray.h"
#include "Intersect.h"
#include "Camera.h"

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
    void OnRender();

    glm::vec4 WritePerPixel(uint32_t x, uint32_t y);
    glm::vec3 CalculateRay(const Ray& ray, int depth);
    uint32_t ConvertToRGBA(glm::vec4& color);
    void RandomSpheres();

private:
    bool m_Show;
    Simulacra::Shader m_QuadShader;

    Simulacra::Texture m_SceneTexture;
    glm::vec4* m_DataPtr = nullptr;
    uint32_t* m_ImageData = nullptr;

    std::vector<uint32_t> m_HorizontalPixels;
    std::vector<uint32_t> m_VerticalPixels;
};