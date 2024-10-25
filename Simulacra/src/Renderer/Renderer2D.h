#pragma once

#include <glm/glm.hpp>

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Simulacra
{
    void StartRendererSubsystem();

    void BeginScene();
    void EndScene();

    void DrawSprite(const Texture& texture, const glm::mat4& transform, float spriteWidth = 0, float spriteHeight = 0, float xoffset = 0, float yoffset = 0);
}