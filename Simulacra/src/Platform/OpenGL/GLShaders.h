#pragma once

#include <string>
#include <array>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Simulacra
{
    struct Shader 
    {
        uint32_t ProgramID;
        std::array<std::string, 5> Sources;
    };

    Shader LoadShaders(const std::string& path);
    void SetActiveShader(uint32_t program);

    void SetIntUniform(const Shader& shader, const std::string& location, int i);
    void SetIntUniform(const Shader& shader, const std::string& location, int i, int j);
    void SetIntUniform(const Shader& shader, const std::string& location, int i, int j, int k);

    void SetFloatUniform(const Shader& shader, const std::string& location, float i);
    void SetFloatUniform(const Shader& shader, const std::string& location, float i, float j);
    void SetFloatUniform(const Shader& shader, const std::string& location, float i, float j, float k);

    void SetMatfUniform(const Shader& shader, const std::string& location, glm::mat4 transform);
    void SetMatfUniform(const Shader& shader, const std::string& location, glm::mat3 transform);
    void SetMatfUniform(const Shader& shader, const std::string& location, glm::mat2 transform);
}