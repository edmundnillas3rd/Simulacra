#pragma once

#include <string>

#include <glad/glad.h>

struct Shader
{
    GLuint ID;
};

GLuint LoadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath = "");
void UseShader(GLuint id);
void SetUniformInt(GLuint program, const GLchar* name, GLint value);