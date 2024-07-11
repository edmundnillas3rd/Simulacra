#pragma once

#include "src/Platform/OpenGL/Shaders.h"
#include "src/Platform/OpenGL/Buffers.h"
#include "src/Platform/OpenGL/Texture.h"

namespace Simulacra
{
    void DrawIndices(Shader shader, VertexArrayBuffer object, uint32_t count);
}