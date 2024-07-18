#include "Renderer.h"

#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Simulacra
{
    struct QuadData
    {
        std::array<float, 24> Vertices;
        std::array<uint32_t, 6> Indices;
    };

    struct RendererData
    {
        Shader SceneShader;

        // Quad
        VertexArrayBuffer QuadArray;
        VertexBuffer QuadBuffer;
        ElementBuffer QuadIndices;
        QuadData QuadVertices;
    };

    RendererData n_Data;

    void InitializeRenderer()
    {
        n_Data.QuadVertices.Vertices = {
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 1.0f
        };

        n_Data.QuadVertices.Indices = {
            0, 1, 3,
            1, 2, 3
        };

        n_Data.QuadArray = CreateVertexArrayBuffer();

        n_Data.QuadBuffer = CreateVertexBuffer();
        BufferVertexBuffer(sizeof(n_Data.QuadVertices.Vertices), n_Data.QuadVertices.Vertices.data());

        n_Data.QuadIndices = CreateElementBuffer(6);
        BufferElementBuffer(sizeof(n_Data.QuadVertices.Indices), n_Data.QuadVertices.Indices.data());

        SetVertexAttribute(0, 4, 6 * sizeof(float), (void*)0);
        SetVertexAttribute(1, 2, 6 * sizeof(float), (void*)(4 * sizeof(float)));

        n_Data.SceneShader = LoadShaders("assets/shaders/default.glsl");
        SetActiveShader(n_Data.SceneShader.ProgramID);
    }

    void DrawSprite(const Texture& texture, glm::vec2 position)
    {
        BindTexture(texture.TextureID);
        BindVertexArrayBuffer(n_Data.QuadArray.RendererID);
        DrawIndices(n_Data.QuadIndices.IndexCount);
    }
}