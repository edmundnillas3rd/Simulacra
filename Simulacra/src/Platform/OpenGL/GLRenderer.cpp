#include "src/Simulacra/Renderer/Renderer.h"

#include <glad/glad.h>

#include "src/Simulacra/Window.h"

namespace Simulacra
{
    struct Renderer2D : Renderer
    {
        // Default vertices for drawing a 2D texture
        std::array<float, 20> Vertices;
        std::array<uint32_t, 6> Indices;

        VertexArrayBuffer SpriteVAO;
        VertexBuffer SpriteVBO;
        ElementBuffer SpriteEBO;
    };

    Renderer2D* n_Renderer;

    // The set vertices for the quad
    std::array<float, 24> QuadVertices;

    Renderer* CreateRenderer();

    void InitializeRenderer()
    {
        n_Renderer = nullptr;
        n_Renderer = reinterpret_cast<Renderer2D*>(CreateRenderer());

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
        Renderer2D* renderer = new Renderer2D();

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

        return renderer;
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

