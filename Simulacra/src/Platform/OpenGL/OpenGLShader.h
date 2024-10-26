#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Simulacra
{
    struct Shader
    {
        uint32_t ProgramID;
    };

    Shader LoadShaders(const std::vector<std::string>& paths);
    void UseShader(const Shader& shader);

    void SetShaderIntUniform(const Shader& shader, const std::string& name, int value);
    void SetShaderMat4Uniform(const Shader& shader, const std::string& name, const glm::mat4& value);
}