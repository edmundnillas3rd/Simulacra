#include "OpenGLRenderer.h"
#include <array>

#include <glad/glad.h>

#include "../../Core/Logger.h"

namespace Simulacra
{
    struct GLRenderer
    {
        uint32_t Buffer;
        uint32_t VertexArrayBuffer;

        static constexpr uint32_t MAX_QUADS = 40000;
        static constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
        static constexpr uint32_t MAX_INDICES = MAX_QUADS * 6;
        static constexpr uint32_t MAX_TEXTURE_SLOTS = 16;

        uint32_t QuadCount;

        std::array<float, MAX_VERTICES> Quads;
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

        glBufferData(GL_ARRAY_BUFFER, GLRenderer::MAX_VERTICES * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    }

    void DestroyOpenGLRenderer()
    {
    }

    void BeginRender()
    {
        s_Renderer.QuadCount = 0;
        s_Renderer.Quads.fill(0.0f);
    }

    void BeginRender(const Shader& shader)
    {
        s_Renderer.SceneShader = shader;

        s_Renderer.QuadCount = 0;
        s_Renderer.Quads.fill(0.0f);
    }

    void EndRender()
    {
        glBindVertexArray(s_Renderer.VertexArrayBuffer);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * s_Renderer.QuadCount, s_Renderer.Quads.data());

        UseShader(s_Renderer.SceneShader);
        glDrawArrays(GL_TRIANGLES, 0, s_Renderer.QuadCount);
    }

    void DrawVertices()
    {
        s_Renderer.Quads[s_Renderer.QuadCount + 0] =  0.0f;
        s_Renderer.Quads[s_Renderer.QuadCount + 1] =  0.5f;
        s_Renderer.Quads[s_Renderer.QuadCount + 2] =  0.0f;

        s_Renderer.Quads[s_Renderer.QuadCount + 3] =  0.5f;
        s_Renderer.Quads[s_Renderer.QuadCount + 4] = -0.5f;
        s_Renderer.Quads[s_Renderer.QuadCount + 5] =  0.0f;

        s_Renderer.Quads[s_Renderer.QuadCount + 6] = -0.5f;
        s_Renderer.Quads[s_Renderer.QuadCount + 7] = -0.5f;
        s_Renderer.Quads[s_Renderer.QuadCount + 8] =  0.0f;

        s_Renderer.QuadCount += 8;
    }
}