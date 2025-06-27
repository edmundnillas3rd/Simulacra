#pragma once
#include "OpenGLShader.h"

namespace Simulacra
{
    void CreateOpenGLRenderer();
    void DestroyOpenGLRenderer();

    void BeginRender();
    void BeginRender(const Shader& shader);

    void EndRender();

    void DrawVertices();
}