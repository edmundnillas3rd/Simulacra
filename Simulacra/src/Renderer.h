#pragma once

#include <vector>

#include "Platform/OpenGL/Texture.h"

namespace Simulacra
{
    void InitializeRenderer();
    void RenderTexture(Texture texture);

    void DrawLine();
}