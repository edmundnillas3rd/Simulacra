#include "Renderer.h"

#include <cstddef>
#include <array>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Simulacra
{
    struct Sprite
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
    };

    struct RendererData
    {
        static const uint32_t MAX_QUADS = 40000;
        static const uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static const uint32_t MAX_INDICES = MAX_QUADS * 6;

        uint32_t IndexCount;

        Shader SceneShader;

        // Quad
        VertexArrayBuffer QuadArray;
        VertexBuffer QuadBuffer;
        ElementBuffer QuadIndices;

        Sprite* Sprites;
        Sprite* SpritePtr;

        std::array<glm::vec4, 4> QuadPositions;
    };

    RendererData n_Data;

    void CreateRenderer()
    {
        n_Data.IndexCount = 0;
        n_Data.QuadArray = CreateVertexArrayBuffer();

        n_Data.QuadBuffer = CreateVertexBuffer();
        BufferVertexBuffer(sizeof(Sprite) * n_Data.MAX_VERTICES);

        n_Data.Sprites = new Sprite[n_Data.MAX_VERTICES];

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

        SetVertexAttribute(0, 3, sizeof(Sprite), (void*)offsetof(Sprite, Position));
        SetVertexAttribute(1, 4, sizeof(Sprite), (void*)offsetof(Sprite, Color));
        SetVertexAttribute(2, 2, sizeof(Sprite), (void*)offsetof(Sprite, TexCoords));

        n_Data.SceneShader = LoadShaders("assets/shaders/default.glsl");
        SetActiveShader(n_Data.SceneShader.ProgramID);
    }

    void DestroyRenderer()
    {
        delete[] n_Data.Sprites;
    }

    void BeginRender()
    {
        n_Data.IndexCount = 0;
        n_Data.SpritePtr = n_Data.Sprites;
    }

    void EndRender()
    {
        if (n_Data.IndexCount)
        {
            uint32_t dataSize = (uint32_t)((uint8_t*)n_Data.SpritePtr - (uint8_t*)n_Data.Sprites);
            SetActiveShader(n_Data.SceneShader.ProgramID);
            BindVertexArrayBuffer(n_Data.QuadArray.RendererID);
            BufferSubVertexBuffer(0, dataSize, n_Data.Sprites);

            DrawIndices(n_Data.IndexCount);
        }
    }

    void DrawQuad(const Texture& texture, const glm::mat4 transform)
    {
		const glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
        const glm::vec4 tintColor = { 1.0f, 1.0f, 1.0f, 1.0f };

        for (size_t i = 0; i < n_Data.QuadPositions.size(); i++)
        {
            n_Data.SpritePtr->Position = transform * n_Data.QuadPositions[i];
            n_Data.SpritePtr->Color = tintColor;
            n_Data.SpritePtr->TexCoords = textureCoords[i];
            n_Data.SpritePtr++;
        }

        n_Data.IndexCount += 6;
    }

    void DrawSprite(const Texture& texture, glm::vec3 position)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position);
        DrawQuad(texture, transform);
    }
}