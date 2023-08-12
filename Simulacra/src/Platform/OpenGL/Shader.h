#pragma once

#include <glad/glad.h>

namespace Simulacra
{
    struct Shader
    {
        std::vector<GLuint> IDs;
    };

    Shader LoadShader(std::vector<std::string> paths, bool tessellation = false, bool geometry = false);
}
