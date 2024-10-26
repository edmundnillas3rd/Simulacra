#pragma once

#include <string>
#include <vector>

namespace Simulacra
{
    struct Shader
    {
        uint32_t ProgramID;
    };

    Shader LoadShaders(const std::vector<std::string>& paths);
    void UseShader(const Shader& shader);

    void SetShaderIntUniform(const Shader& shader, const std::string& name, int value);
}