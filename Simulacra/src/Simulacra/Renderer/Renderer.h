#pragma once

#include <string>

#include <glm/glm.hpp>

#include "src/Simulacra/Camera.h"
#include "src/Platform/OpenGL/GLRenderer.h"

namespace Simulacra
{
    struct Renderer
    {
        std::string Name;
    };

    void CreateRenderer();
    void DestroyRenderer();
    
    // For 2D Rendering
    void BeginRender();
    void BeginRender(const OrthographicCamera& camera);
    void EndRender();

    void DrawQuad(const Texture& texture);
    void DrawQuad(const Texture& texture, const glm::mat4 transform);
    void DrawSprite(const Texture& texture, glm::vec3 position);
}