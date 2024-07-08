#pragma once

#include <string>
#include <iostream>

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Simulacra
{
    struct Texture
    {
        glm::ivec2 Texels;
        GLuint Buffer;
    };

    Texture LoadTexture(const std::string& path);
    void BindTexture(GLuint texture = 0);
}