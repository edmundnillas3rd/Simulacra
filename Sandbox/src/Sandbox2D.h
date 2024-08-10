#pragma once

#include <thread>

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
private:
    glm::vec4 PerPixel(uint32_t x, uint32_t y);

    bool m_Show;
    Simulacra::Shader m_QuadShader;

    Simulacra::Texture m_SceneTexture;
    glm::vec4* m_DataPtr = nullptr;
    uint32_t* m_ImageData = nullptr;

    std::vector<uint32_t> m_HorizontalPixels;
    std::vector<uint32_t> m_VerticalPixels;
};