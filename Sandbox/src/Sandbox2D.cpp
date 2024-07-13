#include "Sandbox2D.h"

#include <glad/glad.h>

Sandbox2D::Sandbox2D()
{
    m_QuadVertices = {
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    m_Vertices = {
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
    };

    m_Indices = {
        0, 1, 3,
        1, 2, 3
    };
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    // Draw the contents of the scene to the framebuffer
    m_Framebuffer = Simulacra::CreateFramebuffer("Main");
    m_SceneShader = Simulacra::LoadShaders("assets/shaders/default.glsl");
    m_VAO = Simulacra::CreateVertexArrayBuffer();
    m_VBO = Simulacra::CreateVertexBuffer();
    m_EBO = Simulacra::CreateElementBuferObject();

    Simulacra::BindVertexArrayBuffer(m_VAO.RendererID);

    Simulacra::BindVertexBuffer(m_VBO.RendererID);
    Simulacra::BufferVertexBuffer(sizeof(m_Vertices), (void*)m_Vertices.data());
        
    Simulacra::BindElementBuffer(m_EBO.RendererID);
    Simulacra::BufferElementBuffer(sizeof(m_Indices), (void*)m_Indices.data());

    Simulacra::SetVertexAttribute(0, 3, sizeof(float) * 5, (void*)0);
    Simulacra::SetVertexAttribute(1, 2, sizeof(float) * 5, (void*)(sizeof(float) * 3));

    m_Texture = Simulacra::LoadTexture("assets/images/container.jpg");

    m_ScreenShader = Simulacra::LoadShaders("assets/shaders/default-screen.glsl");
    m_QuadVAO = Simulacra::CreateVertexArrayBuffer();
    m_QuadVBO = Simulacra::CreateVertexBuffer();
    Simulacra::BufferVertexBuffer(sizeof(m_QuadVertices), (void*)m_QuadVertices.data());
    Simulacra::SetVertexAttribute(0, 3, 4 * sizeof(float), (void*)0);
    Simulacra::SetVertexAttribute(1, 2, 4 * sizeof(float), (void*)(sizeof(float) * 2));

    m_ScreenTexture = Simulacra::CreateTextureAttachment();

    Simulacra::SetActiveShader(m_ScreenShader.ProgramID);
    Simulacra::SetIntUniform(m_ScreenShader, "OutTex", 0);

    std::cout << "Layer Attached" << std::endl;
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    // Drawing Sample of a Framebuffer (Render to Texture)
    Simulacra::BindFramebuffer(m_Framebuffer.ID);
    glEnable(GL_DEPTH_TEST);

    // NOTE(Edmund): could be put in its own function
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Simulacra::SetActiveShader(m_SceneShader.ProgramID);
    Simulacra::BindVertexArrayBuffer(m_VAO.RendererID);
    Simulacra::SetActiveTexture(0);
    Simulacra::BindTexture(m_Texture.TextureID);
    Simulacra::DrawIndices(m_SceneShader, m_VAO, 6);

    Simulacra::BindFramebuffer(0);
    glDisable(GL_DEPTH_TEST);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Simulacra::SetActiveShader(m_ScreenShader.ProgramID);
    Simulacra::BindVertexArrayBuffer(m_QuadVAO.RendererID);
    Simulacra::BindTexture(m_ScreenTexture.TextureID);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Sandbox2D::OnImGuiRender()
{
}

void Sandbox2D::OnEvent(Simulacra::Event& event)
{
}
