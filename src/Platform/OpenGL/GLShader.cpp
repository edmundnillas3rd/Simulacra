#include "GLShader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "GLDebug.h"

static void CheckCompileErrors(unsigned int shader, std::string type);

uint32_t LoadShader(const std::string& vertexPath, const std::string& fragmentPath, const std::string& geometryPath)
{
    uint32_t ID = 0;

    std::ifstream vertexShaderFile, fragmentShaderFile, geometryShaderFile;
    std::stringstream vertexStream, fragmentStream, geometryStream;
    std::string vertexCode, fragmentCode, geometryCode;

    vertexShaderFile.open(vertexPath.c_str());
    fragmentShaderFile.open(fragmentPath.c_str());

    vertexStream << vertexShaderFile.rdbuf();
    fragmentStream << fragmentShaderFile.rdbuf();

    vertexShaderFile.close();
    fragmentShaderFile.close();

    vertexCode = vertexStream.str();
    fragmentCode = fragmentStream.str();

    if (!geometryPath.empty())
    {
        geometryShaderFile.open(geometryPath.c_str());
        geometryStream << geometryShaderFile.rdbuf();
        geometryShaderFile.close();
        geometryCode = geometryStream.str().c_str();
    }

    const char* vertexSource = vertexCode.c_str();
    const char* fragmentSource = fragmentCode.c_str();

    uint32_t vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexSource, nullptr);
    glCompileShader(vertex);
    CheckCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentSource, nullptr);
    glCompileShader(fragment);
    CheckCompileErrors(fragment, "FRAGMENT");
    
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    CheckCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);

    return ID;
}

void UseShader(GLuint id)
{
    glUseProgram(id);
    glCheckError();
}

void SetUniformInt(GLuint program, const GLchar* name, GLint value)
{
    glUniform1i(glGetUniformLocation(program, name), value);
    glCheckError();
}

static void CheckCompileErrors(unsigned int shader, std::string type)
{
    int success;
    char infoLog[1024];
    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}
