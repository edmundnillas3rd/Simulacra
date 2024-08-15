#include "Renderer.h"

#include <cstddef>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "src/Simulacra/Window.h"

namespace Simulacra
{
    struct SpriteVertices
    {
        glm::vec3 Position;
        glm::vec4 Color;

        // NOTE(Edmund): Supposedly, it should be vec4 instead of vec2, but
        // I've tried to seperate the texture offset properties in order to maintain
        // the struct according to the opengl data format for drawing quads

        // [0]: the x position of the texture rect
        // [1]: the y position of the texture rect
        // [2]: the width of the texture rect
        // [3]: the height of the texture rect
        glm::vec2 TexCoords;
        float TexIndex;
    };

    struct RendererData
    {
        static const uint32_t MAX_QUADS = 8000;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;
        static const uint32_t MAX_TEXTURES = 8;

        uint32_t IndexCount;

        Shader SpriteQuadShader;

        // Quad
        VertexArrayBuffer QuadArray;
        VertexBuffer QuadBuffer;
        ElementBuffer QuadIndices;

        SpriteVertices* Sprites;
        SpriteVertices* SpritePtr;

        std::array<glm::vec4, 4> QuadPositions;

        std::array<Texture, MAX_TEXTURES> Textures;
        uint32_t TextureSlotIndex = 0;
        
        struct CameraData
        {
            glm::mat4 ViewProjection;
        };

        CameraData SceneCamera;
        UniformBuffer CameraBuffer;
    };

    RendererData n_Data;

    void CreateRenderer()
    {
        n_Data.IndexCount = 0;
        n_Data.QuadArray = CreateVertexArrayBuffer();

        n_Data.QuadBuffer = CreateVertexBuffer();
        BufferVertexBuffer(sizeof(SpriteVertices) * n_Data.MAX_VERTICES);

        n_Data.Sprites = new SpriteVertices[n_Data.MAX_VERTICES];

        n_Data.QuadIndices = CreateElementBuffer();

        std::array<uint32_t, n_Data.MAX_INDICES> Indices;

        uint32_t offset = 0;
        for (size_t i = 0; i < n_Data.MAX_INDICES; i += 6)
        {
            Indices[i + 0] = offset + 0;
            Indices[i + 1] = offset + 1;
            Indices[i + 2] = offset + 2;

            Indices[i + 3] = offset + 2;
            Indices[i + 4] = offset + 3;
            Indices[i + 5] = offset + 0;
            offset += 4;
        }

        BufferElementBuffer(n_Data.MAX_INDICES, Indices.data());

        n_Data.QuadPositions[0] = {  0.5f,  0.5f, 0.0f, 1.0f };
        n_Data.QuadPositions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
        n_Data.QuadPositions[2] = { -0.5f, -0.5f, 0.0f, 1.0f };
        n_Data.QuadPositions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

        SetVertexAttribute(0, 3, sizeof(SpriteVertices), (void*)offsetof(SpriteVertices, Position));
        SetVertexAttribute(1, 4, sizeof(SpriteVertices), (void*)offsetof(SpriteVertices, Color));
        SetVertexAttribute(2, 2, sizeof(SpriteVertices), (void*)offsetof(SpriteVertices, TexCoords));
        SetVertexAttribute(3, 1, sizeof(SpriteVertices), (void*)offsetof(SpriteVertices, TexIndex));

        n_Data.SpriteQuadShader = LoadShaders("assets/shaders/default.glsl");
        UseShaderProgram(n_Data.SpriteQuadShader.ProgramID);

        auto window = GetCurrentWindow();
        n_Data.CameraBuffer = CreateUniformBuffer(sizeof(RendererData::CameraData), 0);
    }

    void DestroyRenderer()
    {
        delete[] n_Data.Sprites;
    }

    void Flush()
    {
        if (n_Data.IndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)n_Data.SpritePtr - (uint8_t*)n_Data.Sprites);
            BindVertexArrayBuffer(n_Data.QuadArray.RendererID);
            BufferSubVertexBuffer(0, dataSize, n_Data.Sprites);

            for (uint32_t i = 0; i < n_Data.TextureSlotIndex; i++)
                BindTexture(i, n_Data.Textures[i].TextureID);

            UseShaderProgram(n_Data.SpriteQuadShader.ProgramID);
            DrawIndices(n_Data.IndexCount);
        }
    }

    void StartBatch()
    {
        n_Data.IndexCount = 0;
        n_Data.SpritePtr = n_Data.Sprites;

        n_Data.TextureSlotIndex = 0;
    }

    void NextBatch()
    {
        Flush();
        StartBatch();
    }

    void BeginRender()
    {
        StartBatch();
    }

    void BeginRender(const OrthographicCamera &camera)
    {
        n_Data.SceneCamera.ViewProjection = CalculateViewProjectionMatrix(camera);
        BufferUniformBuffer(n_Data.CameraBuffer.RendererID, 0, sizeof(RendererData::CameraData), (void*)&n_Data.SceneCamera);

        StartBatch();
    }

    void EndRender()
    {
        Flush();
    }

    // For rendering the screen quad
    void DrawQuad(const Texture& texture)
    {
        float textureIndex = 0.0f;
		const glm::vec2 textureCoords[] = { 
            { 1.0f, 1.0f }, 
            { 1.0f, 0.0f }, 
            { 0.0f, 0.0f }, 
            { 0.0f, 1.0f } 
        };

        const glm::vec4 tintColor = { 1.0f, 1.0f, 1.0f, 1.0f };

        if (n_Data.IndexCount >= RendererData::MAX_INDICES)
            NextBatch();

        const glm::vec3 FlipQuadPositions[] = {
            {  1.0f,  1.0f, 0.0f },
            {  1.0f, -1.0f, 0.0f },
            { -1.0f, -1.0f, 0.0f },
            { -1.0f,  1.0f, 0.0f }
        };

        for (size_t i = 0; i < n_Data.QuadPositions.size(); i++)
        {
            n_Data.SpritePtr->Position = FlipQuadPositions[i];
            n_Data.SpritePtr->Color = tintColor;
            n_Data.SpritePtr->TexCoords = textureCoords[i];
            n_Data.SpritePtr->TexIndex = textureIndex;
            n_Data.SpritePtr++;
        }

        n_Data.IndexCount += 6;
    }

    void DrawQuad(const Texture& texture, const glm::mat4 transform)
    {
		const glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const glm::vec4 tintColor = glm::vec4(1.0f);

        if (n_Data.IndexCount >= RendererData::MAX_INDICES)
            NextBatch();

        float textureIndex = 0.0f;
        for (uint32_t i = 0; i < n_Data.TextureSlotIndex; i++)
        {
            if (n_Data.Textures[i].TextureID == texture.TextureID)
            {
                textureIndex = (float)i;
                break;
            }
        }

        if (textureIndex == 0.0f)
        {
            if (n_Data.TextureSlotIndex >= n_Data.MAX_TEXTURES)
                NextBatch();

            textureIndex = (float)n_Data.TextureSlotIndex;
            n_Data.Textures[n_Data.TextureSlotIndex] = texture;
            n_Data.TextureSlotIndex++;
        }

        for (size_t i = 0; i < n_Data.QuadPositions.size(); i++)
        {
            n_Data.SpritePtr->Position = transform * n_Data.QuadPositions[i];
            n_Data.SpritePtr->Color = tintColor;
            n_Data.SpritePtr->TexCoords = textureCoords[i];
            n_Data.SpritePtr->TexIndex = textureIndex;
            n_Data.SpritePtr++;
        }

        n_Data.IndexCount += 6;
    }

    void DrawSprite(const Texture& texture, glm::vec3 position)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), glm::vec3(position.x, position.y, 0.0f));
        transform = glm::scale(transform, glm::vec3(texture.Width, texture.Height, 0.0f));
        DrawQuad(texture, transform);
    }
}