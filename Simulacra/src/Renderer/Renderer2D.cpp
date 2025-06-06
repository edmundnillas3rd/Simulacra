#include "Renderer2D.h"

#include <array>

#include <glm/gtc/matrix_transform.hpp>

#include "src/Logger.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Simulacra
{
    struct Sprite
    {
        glm::vec3 Position;
        glm::vec2 TexCoord;
        float TexIndex;
    };

    struct RendererData
    {
        static const uint32_t MAX_QUADS = 20000;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_TEXTURE_SLOTS = 16;

        Buffer QuadArrayBuffer;
        Buffer QuadVertexBuffer;
        Buffer QuadIndexBuffer;
        std::array<Sprite, MAX_VERTICES> QuadVertices;

        std::array<glm::vec4, 4> QuadPositions;

        Texture DefaultWhiteTex;
        std::array<Texture, MAX_TEXTURE_SLOTS> Textures;
        uint32_t TextureSlotIndex;

        uint32_t QuadCount;
        uint32_t IndexCount;

        Shader SceneShader;
    };

    static RendererData s_Renderer;

    void StartRendererSubsystem()
    {
        s_Renderer.QuadCount = 0;
        s_Renderer.IndexCount = 0;

        s_Renderer.QuadArrayBuffer = CreateVertexArray();
        BindVertexArray(s_Renderer.QuadArrayBuffer);

        s_Renderer.QuadVertexBuffer = CreateBuffer();
        BindBuffer(s_Renderer.QuadVertexBuffer);

        AllocateSizeBuffer(sizeof(Sprite) * RendererData::MAX_VERTICES);

        s_Renderer.QuadIndexBuffer = CreateBuffer();
        BindIndexBuffer(s_Renderer.QuadIndexBuffer);

        std::array<uint32_t, RendererData::MAX_INDICES> QuadIndices;

        uint32_t offset = 0;
        for (size_t i = 0; i < RendererData::MAX_INDICES; i += 6)
        {
            QuadIndices[i + 0] = offset + 0;
            QuadIndices[i + 1] = offset + 1;
            QuadIndices[i + 2] = offset + 2;

            QuadIndices[i + 3] = offset + 2;
            QuadIndices[i + 4] = offset + 3;
            QuadIndices[i + 5] = offset + 0;
            offset += 4;
        }

        WriteIndexData(RendererData::MAX_INDICES, QuadIndices.data());

        SetVertexAttrib(0, 3, sizeof(Sprite), (void*)offsetof(Sprite, Position));
        SetVertexAttrib(1, 2, sizeof(Sprite), (void*)offsetof(Sprite, TexCoord));
        SetVertexAttrib(2, 1, sizeof(Sprite), (void*)offsetof(Sprite, TexIndex));

        s_Renderer.DefaultWhiteTex = CreateTexture();
        uint32_t whiteTextureData = 0xffffffff;
        WriteTexture(s_Renderer.DefaultWhiteTex, &whiteTextureData);

        s_Renderer.SceneShader = LoadShaders({
            "Sandbox/assets/shaders/main.vert",
            "Sandbox/assets/shaders/main.frag"
        });

        UseShader(s_Renderer.SceneShader);

        s_Renderer.Textures[0] = s_Renderer.DefaultWhiteTex;

        s_Renderer.TextureSlotIndex = 1;

        s_Renderer.QuadPositions[0] = {  0.5f,  0.5f, 0.0f, 1.0f }; // Top right
        s_Renderer.QuadPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f }; // Bottom right
        s_Renderer.QuadPositions[2] = { -0.5f, -0.5f, 0.0f, 1.0f }; // Bottom left
        s_Renderer.QuadPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f }; // Top left

        int samples[RendererData::MAX_TEXTURE_SLOTS];

        // NOTE(Edmund): On some systems this may not work
        for (uint32_t i = 0; i < RendererData::MAX_TEXTURE_SLOTS; i++)
            SetShaderIntUniform(s_Renderer.SceneShader, "u_TextureSlots[" + std::to_string(i) + "]", i);

    }

    static void Flush()
    {
        if (s_Renderer.IndexCount)
        {
            BindVertexArray(s_Renderer.QuadArrayBuffer);
            WriteData(0, sizeof(Sprite) * s_Renderer.QuadCount, s_Renderer.QuadVertices.data());

            for (uint32_t i = 0; i < s_Renderer.TextureSlotIndex; i++)
            {
                SetActiveTexture(i);
                BindTexture(s_Renderer.Textures[i]);
            }

            UseShader(s_Renderer.SceneShader);
            DrawIndex(s_Renderer.IndexCount);
        }
    }

    static void StartBatch()
    {
        s_Renderer.QuadCount = 0;
        s_Renderer.IndexCount = 0;

        s_Renderer.QuadVertices.fill({});

        s_Renderer.TextureSlotIndex = 1;
    }

    void BeginScene()
    {
        StartBatch();
    }

    void BeginScene(const OrthographicCamera& camera)
    {
        SetShaderMat4Uniform(s_Renderer.SceneShader, "u_ViewProjMat", CalculateViewProj(camera));
        StartBatch();
    }

    void EndScene()
    {
        Flush();
    }

    static void NextBatch()
    {
        Flush();
        StartBatch();
    }

    void DrawQuad(const Texture& texture, const glm::mat4& transform)
    {
        const glm::vec2 texCoords[4] = {
            { 1.0f, 1.0f },
            { 1.0f, 0.0f },
            { 0.0f, 0.0f },
            { 0.0f, 1.0f }
        };

        if (s_Renderer.IndexCount >= RendererData::MAX_INDICES)
            NextBatch();

        for (size_t i = 0; i < 4; i++)
        {
            uint32_t currentVertCount = s_Renderer.QuadCount + i;
            s_Renderer.QuadVertices[currentVertCount].Position = transform * s_Renderer.QuadPositions[i];
            s_Renderer.QuadVertices[currentVertCount].TexCoord = texCoords[i];
            s_Renderer.QuadVertices[currentVertCount].TexIndex = 0.0f;
        }

        s_Renderer.IndexCount += 6;
        s_Renderer.QuadCount += 4;
    }

    void DrawQuad(const Texture& texture, const glm::mat4& transform, float spriteWidth, float spriteHeight, float xoffset, float yoffset)
    {
        float px = 1.0f / (float)texture.Width;
        float halfPx = px * 0.5f;
        float py = 1.0f / (float)texture.Height;
        float halfPy = py * 0.5f;

        float sprites[4]= {
            // xoffset * px - halfPx,
            // yoffset * py - halfPy,
            xoffset * px - px,
            yoffset * py - py,
            spriteWidth * px + px,
            spriteHeight * py + py
        };

        // NOTE(Edmund): Magmahay ko og taman ani pag abot sa panahon
        // ako ra nag hatag kalisod sa akong kaugalingon
        const glm::vec2 texCoords[4] = {
            { sprites[0] + sprites[2],  sprites[1] + sprites[3] },
            { sprites[0] + sprites[2],  sprites[1]              },
            { sprites[0],  sprites[1]                           },
            { sprites[0],  sprites[1] + sprites[3]              },
        };

        if (s_Renderer.IndexCount >= RendererData::MAX_INDICES)
            NextBatch();

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Renderer.TextureSlotIndex; i++)
        {
            if (s_Renderer.Textures[i].TextureID == texture.TextureID)
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (s_Renderer.TextureSlotIndex >= RendererData::MAX_TEXTURE_SLOTS)
                NextBatch();

            textureIndex = (float)s_Renderer.TextureSlotIndex;
            s_Renderer.Textures[s_Renderer.TextureSlotIndex] = texture;
            s_Renderer.TextureSlotIndex++;
        }

        for (size_t i = 0; i < 4; i++)
        {
            uint32_t currentVertCount = s_Renderer.QuadCount + i;
            s_Renderer.QuadVertices[currentVertCount].Position = transform * s_Renderer.QuadPositions[i];
            s_Renderer.QuadVertices[currentVertCount].TexCoord = texCoords[i];
            s_Renderer.QuadVertices[currentVertCount].TexIndex = textureIndex;
        }

        s_Renderer.IndexCount += 6;
        s_Renderer.QuadCount += 4;
    }

    void DrawSprite(const Texture& texture, const glm::mat4& transform, float spriteWidth, float spriteHeight, float xoffset, float yoffset)
    {
        glm::mat4 t = transform;
        if (spriteWidth > 0 && spriteHeight > 0)
        {
            t = glm::scale(transform, glm::vec3(spriteWidth, spriteHeight, 1.0f));
            DrawQuad(texture, t, spriteWidth, spriteHeight, xoffset, yoffset);
        }
        else
        {
            DrawQuad(texture, t);
        }
    }
}