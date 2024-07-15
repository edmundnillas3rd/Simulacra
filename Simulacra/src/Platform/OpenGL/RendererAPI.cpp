#include "src/Simulacra/Renderer.h"

#include <glad/glad.h>

#include "src/Simulacra/Window.h"

namespace Simulacra
{
    struct RendererAPI : Renderer
    {
        // Default vertices for drawing a 2D texture
        std::array<float, 20> Vertices;
        std::array<uint32_t, 6> Indices;

        VertexArrayBuffer SpriteVAO;
        VertexBuffer SpriteVBO;
        ElementBuffer SpriteEBO;
    };

    RendererAPI* n_Renderer;

    // The set vertices for the quad
    std::array<float, 24> QuadVertices;

    Renderer* CreateRenderer();

    void InitializeRenderer()
    {
        n_Renderer = nullptr;
        n_Renderer = reinterpret_cast<RendererAPI*>(CreateRenderer());

        // The quad to be drawn to
        QuadVertices = {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };
    }

    #define TEX_ATTCH_WIDTH 1280
    #define TEX_ATTCH_HEIGHT 680

    Renderer* CreateRenderer()
    {
        RendererAPI* renderer = new RendererAPI();
        renderer->CurrentFramebuffer = CreateFramebuffer("Main");
        renderer->CurrentFramebuffer.TextureBuffer = CreateTextureAttachment(TEX_ATTCH_WIDTH, TEX_ATTCH_HEIGHT);
        BindFramebuffer(0);

        // [0]: The screen to render
        // [1]: The scene to be drawn into
        renderer->RendererShader[0] = LoadShaders("assets/shaders/default-screen.glsl");
        renderer->RendererShader[1] = LoadShaders("assets/shaders/default.glsl");

    
        renderer->Vertices = {
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
        };

        renderer->Indices = {
            0, 1, 3,
            1, 2, 3
        };

        renderer->SpriteVAO = CreateVertexArrayBuffer();
        BindVertexArrayBuffer(renderer->SpriteVAO.RendererID);

        renderer->SpriteVBO = CreateVertexBuffer();
        BindVertexBuffer(renderer->SpriteVBO.RendererID);
        BufferVertexBuffer(sizeof(renderer->Vertices), (void*)renderer->Vertices.data());
        
        renderer->SpriteEBO = CreateElementBuffer();
        BindElementBuffer(renderer->SpriteEBO.RendererID);
        BufferElementBuffer(sizeof(renderer->Indices), (void*)renderer->Indices.data());

        SetVertexAttribute(0, 3, sizeof(float) * 5, (void*)0);
        SetVertexAttribute(1, 2, sizeof(float) * 5, (void*)(sizeof(float) * 3));

        BindVertexArrayBuffer(0);

        // The quad to be drawn to
        QuadVertices = {
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };

        renderer->CurrentFramebuffer.FramebufferVAO = CreateVertexArrayBuffer();
        BindVertexArrayBuffer(renderer->CurrentFramebuffer.FramebufferVAO.RendererID);

        VertexBuffer vbo = CreateVertexBuffer();
        BindVertexBuffer(vbo.RendererID);
        BufferVertexBuffer(sizeof(QuadVertices), QuadVertices.data());
        SetVertexAttribute(0, 3, sizeof(float) * 4, (void*)0);
        SetVertexAttribute(1, 2, sizeof(float) * 4, (void*)(sizeof(float) * 2));

        BindVertexArrayBuffer(0);

        return renderer;
    }

    void BeginRender()
    {
        BindFramebuffer(n_Renderer->CurrentFramebuffer.ID);
        glViewport(0, 0, TEX_ATTCH_WIDTH, TEX_ATTCH_HEIGHT);

        glEnable(GL_DEPTH_TEST);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        // glClearColor(0.5f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
    
    void EndRender()
    {
        // This renders the framebuffer to screen
        BindFramebuffer(0);
        Window window = GetCurrentWindow();
        glViewport(0, 0, window.Width, window.Height);

        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        SetActiveShader(n_Renderer->RendererShader[0].ProgramID);
        BindVertexArrayBuffer(n_Renderer->CurrentFramebuffer.FramebufferVAO.RendererID);
        BindTexture(n_Renderer->CurrentFramebuffer.TextureBuffer.TextureID);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void DrawIndices(Shader shader, VertexArrayBuffer object, uint32_t count)
    {
        SetActiveShader(shader.ProgramID);
        BindVertexArrayBuffer(object.RendererID);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }

    void DrawSprite(const Texture& texture, glm::mat4 transform)
    {
        SetActiveTexture(0);
        BindTexture(texture.TextureID);

        SetActiveShader(n_Renderer->RendererShader[1].ProgramID);
        SetMatfUniform(n_Renderer->RendererShader[1], "transform", transform);

        BindVertexArrayBuffer(n_Renderer->SpriteVAO.RendererID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    }
}

