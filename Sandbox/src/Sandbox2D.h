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
private:
    bool m_Show;
    // Framebuffer
    Simulacra::Framebuffer m_Framebuffer;
    Simulacra::Shader m_ScreenShader;
    Simulacra::Texture m_ScreenTexture;
    Simulacra::VertexArrayBuffer m_QuadVAO;
    Simulacra::VertexBuffer m_QuadVBO;
    std::array<float, 24> m_QuadVertices;

    // Scene 
    Simulacra::Shader m_SceneShader;
    Simulacra::Texture m_Texture;

    Simulacra::ElementBufferObject m_EBO;
    Simulacra::VertexArrayBuffer m_VAO;
    Simulacra::VertexBuffer m_VBO;
    std::array<float, 20> m_Vertices;
    std::array<uint32_t, 6> m_Indices;
};