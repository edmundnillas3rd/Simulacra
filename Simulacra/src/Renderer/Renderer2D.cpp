#include "Renderer2D.h"

#include <array>

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Simulacra
{
    struct Sprite
    {
        glm::vec3 Position;
        glm::vec2 TexCoord;
    };

    struct RendererData
    {
        static const uint32_t MAX_VERTICES = 5000;
        static const uint32_t MAX_QUAD = MAX_VERTICES * 4;

        Buffer QuadArrayBuffer;
        Buffer QuadVertexBuffer;
        std::array<Sprite, MAX_QUAD> QuadVertices;

        std::array<glm::vec4, 4> QuadPositions;

        uint32_t VertexCount;
        uint32_t QuadCount;

        Shader SceneShader;
    };

    static RendererData s_Renderer;

    void StartRendererSubsystem()
    {
        s_Renderer.VertexCount = 0;
        s_Renderer.QuadCount = 0;

        s_Renderer.QuadVertices.fill({ glm::vec3(0.0f), glm::vec2(0.0f) });

        s_Renderer.QuadPositions[0] = {  0.5f,  0.5f, 0.0f, 1.0f }; // Top right
        s_Renderer.QuadPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f }; // Bottom right
        s_Renderer.QuadPositions[2] = { -0.5f, -0.5f, 0.0f, 1.0f }; // Bottom left
        s_Renderer.QuadPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f }; // Top left

        s_Renderer.QuadArrayBuffer = CreateVertexArray();
        BindVertexArray(s_Renderer.QuadArrayBuffer);

        s_Renderer.QuadVertexBuffer = CreateBuffer();
        BindBuffer(s_Renderer.QuadVertexBuffer);

        AllocateSizeBuffer(sizeof(Sprite) * RendererData::MAX_VERTICES);

        SetVertexAttrib(0, 3, sizeof(Sprite), (void*)offsetof(Sprite, Position));
        SetVertexAttrib(1, 2, sizeof(Sprite), (void*)offsetof(Sprite, TexCoord));

        s_Renderer.SceneShader = LoadShaders({
            "Sandbox/assets/shaders/main.vert",
            "Sandbox/assets/shaders/main.frag"
        });
        UseShader(s_Renderer.SceneShader);
    }

    void Flush()
    {
        BindVertexArray(s_Renderer.QuadArrayBuffer);
        WriteData(0, sizeof(Sprite) * s_Renderer.QuadCount, s_Renderer.QuadVertices.data());
    }

    void BeginScene()
    {
    }

    void EndScene()
    {
        Flush();
    }

    void DrawSprite(const Texture& texture, const glm::mat4& transform, float spriteWidth, float spriteHeight, float xoffset, float yoffset)
    {
        const glm::vec2 texCoords[] = {
            { 1.0f, 1.0f },
            { 1.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 1.0f }
        };

        if (s_Renderer.VertexCount >= RendererData::MAX_QUAD)
            Flush();

        for (size_t i = 0; i < s_Renderer.QuadPositions.size(); i++)
        {
            s_Renderer.QuadVertices[s_Renderer.VertexCount++] = {
                transform * s_Renderer.QuadPositions[i], 
                texCoords[i]
            };
        }

        s_Renderer.QuadCount += 4;
    }
}