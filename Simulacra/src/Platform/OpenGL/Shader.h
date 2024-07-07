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

    void SetIntShader(const std::string& location, int i);
    void SetIntShader(const std::string& location, int i, int j);
}