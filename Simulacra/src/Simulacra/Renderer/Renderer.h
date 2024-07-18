#pragma once

#include <string>

#include <glm/glm.hpp>

#include "src/Platform/OpenGL/GLRenderer.h"

namespace Simulacra
{
    struct Renderer
    {
        std::string Name;
    };

    void InitializeRenderer();
    
    // For 2D Rendering
    void DrawQuad();
    void DrawSprite(const Texture& texture, glm::vec2 position);

    // Tentative
    Shader GetCurrentShader();
}