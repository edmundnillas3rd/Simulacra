#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Simulacra
{
    struct Shader
    {
        std::vector<GLuint> IDs;
    };

    Shader LoadShader(std::vector<std::string> paths);

    void SetShaderMat4(GLuint program, const std::string& name, const glm::mat4& mat4);
}
