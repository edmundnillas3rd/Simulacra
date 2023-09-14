#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D();

    virtual void OnUpdate(float deltaTime) override;
    virtual void OnImGuiRender() override;
    virtual void OnEvent(Simulacra::Event event) override;
private:
    Simulacra::Shader m_Shader;
    Simulacra::Framebuffer m_FBO;
    Simulacra::Camera m_Camera;
    Simulacra::Texture m_Texture;
    
    GLuint m_CubeVAO;
    GLuint m_CubeVBO;

    GLuint m_ColorBuffer;
    GLuint m_RBO;
    GLuint m_QuadVAO;
    GLuint m_QuadVBO;

    bool m_FreeRoam;
    bool firstMouse = true;
    float lastX;
    float lastY;
};