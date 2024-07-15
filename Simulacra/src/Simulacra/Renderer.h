#pragma once

#include <glm/glm.hpp>

#include "src/Platform/OpenGL/Shaders.h"
#include "src/Platform/OpenGL/Buffers.h"
#include "src/Platform/OpenGL/Texture.h"
#include "src/Platform/OpenGL/Framebuffer.h"

namespace Simulacra
{
    struct Renderer
    {
        std::string Name;
        Framebuffer CurrentFramebuffer;
        std::array<Shader, 2> RendererShader;
    };


    void InitializeRenderer();
    void BeginRender();
    void EndRender();

    void DrawIndices(Shader shader, VertexArrayBuffer object, uint32_t count);
    void DrawSprite(const Texture& texture, glm::vec2 pos);
}