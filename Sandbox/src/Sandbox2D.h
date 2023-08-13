#pragma once

#include <Simulacra.h>

class Sandbox2D : public Simulacra::Layer
{
public:
    Sandbox2D();
    virtual ~Sandbox2D();

    virtual void OnUpdate(float deltaTime) override;
    virtual void OnRender() override;
    virtual void OnEvent(Simulacra::Event event) override;

private:
    Simulacra::Shader m_Shader;
    GLuint m_VAO;
};