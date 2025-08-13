#pragma once
#include <glm/glm.hpp>

#include "OpenGLTexture.h"
#include "OpenGLShader.h"

namespace Simulacra
{
    void CreateOpenGLRenderer();
    void DestroyOpenGLRenderer();

    void BeginRender();
    void BeginRender(const Shader& shader);

    void EndRender();

    void DrawVertices(const glm::mat4& Transform);
    void DrawVertices(const Texture& texture, const glm::mat4& Transform);
}