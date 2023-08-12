#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D();

    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnEvent(Simulacra::Event event) override;

private:
    Simulacra::Shader m_Shader;
    GLuint m_VAO;
};