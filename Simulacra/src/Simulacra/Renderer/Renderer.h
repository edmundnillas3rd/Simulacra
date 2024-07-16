#pragma once

#include <glm/glm.hpp>

#include "src/Platform/OpenGL/GLShaders.h"
#include "src/Platform/OpenGL/GLBuffers.h"
#include "src/Platform/OpenGL/GLTexture.h"
#include "src/Platform/OpenGL/GLFramebuffer.h"

namespace Simulacra
{
    struct Renderer
    {
        std::string Name;
        std::array<Shader, 2> RendererShader;
    };


    void InitializeRenderer();

    void DrawIndices(Shader shader, VertexArrayBuffer object, uint32_t count);
}