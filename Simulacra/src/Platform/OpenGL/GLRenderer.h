#pragma once

#include "GLBuffers.h"
#include "GLShaders.h"
#include "GLTexture.h"

namespace Simulacra
{
    void RenderComputeShader(uint32_t width, uint32_t height);
    void DrawIndices(uint32_t count);
}