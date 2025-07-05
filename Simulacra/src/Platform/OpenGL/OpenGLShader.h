#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Simulacra
{
    struct Shader
    {
        uint32_t ProgramID;
    };

    Shader LoadShaders(const std::map<std::string, std::filesystem::path>& paths);
    Shader ReloadShader(const Shader& shader, std::map<std::string, std::filesystem::path> paths);
    void UseShader(const Shader& shader);

    void SetShaderIntUniform(const Shader& shader, const std::string& name, int value);
    void SetShaderIntArrayUni(const Shader& shader, const std::string& name, size_t count, int value[]);
    void SetShaderMat4Uniform(const Shader& shader, const std::string& name, const glm::mat4& value);
}