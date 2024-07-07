#pragma once

#include <string>
#include <array>

#include <glad/glad.h>

namespace Simulacra
{
    struct Shader 
    {
        GLuint Program;
        std::array<std::string, 5> Sources;
    };

    Shader LoadShaders(const std::string& path);
    void SetActiveShader(GLuint program);

    void SetIntUniform(Shader shader, const std::string& location, int i);
    void SetIntUniform(Shader shader, const std::string& location, int i, int j);
    void SetIntUniform(Shader shader, const std::string& location, int i, int j, int k);

    void SetFloatUniform(Shader shader, const std::string& location, float i);
    void SetFloatUniform(Shader shader, const std::string& location, float i, float j);
    void SetFloatUniform(Shader shader, const std::string& location, float i, float j, float k);
}