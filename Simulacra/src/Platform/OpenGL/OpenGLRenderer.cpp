#include "OpenGLRenderer.h"
#include <array>

#include <glad/glad.h>

#include "../../Core/Logger.h"

namespace Simulacra
{
    struct Sprite
    {
        glm::vec3 Position;
        glm::vec2 TexCoords;
        float TexIndex;
    };

    struct GLRenderer
    {
        uint32_t VertexArrayBuffer;
        uint32_t Buffer;
        uint32_t IndexBuffer;

        static constexpr uint32_t MAX_QUADS = 40000;
        static constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static constexpr uint32_t MAX_INDICES = MAX_QUADS * 6;
        static constexpr uint32_t MAX_TEXTURE_SLOTS = 16;

        static constexpr uint32_t MAX_TEXTURE_SLOTST = 16;

        uint32_t QuadCount;
        std::array<glm::vec4, 4> QuadPositions;

        uint32_t QuadIndicesCount;

        std::array<Sprite, MAX_VERTICES> Quads;
        Shader SceneShader;

    };

    static GLRenderer s_Renderer;

    void CreateOpenGLRenderer()
    {
        s_Renderer.QuadCount = 0;
        glGenVertexArrays(1, &s_Renderer.VertexArrayBuffer);
        glBindVertexArray(s_Renderer.VertexArrayBuffer);

        glGenBuffers(1, &s_Renderer.Buffer);
        glBindBuffer(GL_ARRAY_BUFFER, s_Renderer.Buffer);

        glGenBuffers(1, &s_Renderer.IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Renderer.IndexBuffer);

        glBufferData(GL_ARRAY_BUFFER, GLRenderer::MAX_VERTICES * sizeof(Sprite), nullptr, GL_DYNAMIC_DRAW);

        s_Renderer.QuadIndicesCount = 0;

        std::array<uint32_t, GLRenderer::MAX_INDICES> QuadIndices;
        uint32_t offset = 0;
        for (size_t i  = 0; i < GLRenderer::MAX_INDICES; i += 6)
        {
            QuadIndices[i + 0] = offset + 0;
            QuadIndices[i + 1] = offset + 1;
            QuadIndices[i + 2] = offset + 2;

            QuadIndices[i + 3] = offset + 2;
            QuadIndices[i + 4] = offset + 3;
            QuadIndices[i + 5] = offset + 0;
            offset += 4;
        }

        glBufferData(GL_ELEMENT_ARRAY_BUFFER, GLRenderer::MAX_INDICES, QuadIndices.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Sprite), (void*)offsetof(Sprite, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Sprite), (void*)offsetof(Sprite, TexCoords));
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Sprite), (void*)offsetof(Sprite, TexIndex));

        s_Renderer.QuadPositions = {
            glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f),
            glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f),
            glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f),
            glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f)
        };
        // SetShaderIntUniform(s_Renderer.SceneShader, "textureSlot0", 0);
    }

    void DestroyOpenGLRenderer()
    {
    }

    void BeginRender()
    {
        s_Renderer.QuadCount = 0;
        s_Renderer.Quads.fill({});

        s_Renderer.QuadIndicesCount = 0;
    }

    void BeginRender(const Shader& shader)
    {
        s_Renderer.SceneShader = shader;

        s_Renderer.QuadCount = 0;
        s_Renderer.Quads.fill({});

        s_Renderer.QuadIndicesCount = 0;
    }

    void EndRender()
    {
        if (s_Renderer.QuadIndicesCount)
        {
            glBindVertexArray(s_Renderer.VertexArrayBuffer);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Sprite) * s_Renderer.QuadCount, s_Renderer.Quads.data());

            UseShader(s_Renderer.SceneShader);
            glDrawElements(GL_TRIANGLES, s_Renderer.QuadIndicesCount, GL_UNSIGNED_INT, nullptr);
        }
    }

    void DrawVertices(const glm::mat4& Transform)
    {
        const glm::vec2 texCoords[4] = {
            { 1.0f, 1.0f },
            { 1.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
        };

        for (size_t i = 0; i < 4; i++)
        {
            s_Renderer.Quads[s_Renderer.QuadCount + i].Position = Transform * s_Renderer.QuadPositions[i];
            s_Renderer.Quads[s_Renderer.QuadCount + i].TexCoords = texCoords[i];
        }

        s_Renderer.QuadCount += 4;
        s_Renderer.QuadIndicesCount += 6;
    }

    void DrawVertices(const Texture &texture, const glm::mat4 &Transform)
    {
        float texIndex = 0.0f;

        if (texIndex >= GLRenderer::MAX_TEXTURE_SLOTS)
        {
            texIndex = 0.0f;
        }


        const glm::vec2 texCoords[4] = {
            { 1.0f, 1.0f },
            { 1.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 1.0f },
        };

        for (size_t i = 0; i < 4; i++)
        {
            s_Renderer.Quads[s_Renderer.QuadCount + i].Position = Transform * s_Renderer.QuadPositions[i];
            s_Renderer.Quads[s_Renderer.QuadCount + i].TexCoords = texCoords[i];
            s_Renderer.Quads[s_Renderer.QuadCount + i].TexIndex = texIndex;
        }

        s_Renderer.QuadCount += 4;
        s_Renderer.QuadIndicesCount += 6;
    }
}