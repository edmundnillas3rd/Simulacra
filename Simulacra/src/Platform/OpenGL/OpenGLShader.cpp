#include "OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>

#include "../../Platform/FileSystem.h"
#include "../../Core/Logger.h"

namespace Simulacra
{
    Shader LoadShaders(const std::map<std::string, std::filesystem::path>& paths)
    {
        Shader shader;

        std::map<std::string, std::stringstream> shaderSS;
        std::map<std::string, std::string> shaderStr;
        std::fstream fileStream;

        for (const auto& [key, value] : paths)
        {
            fileStream.open(FormatFilepath(value), std::ios::in | std::ios::binary);

            shaderSS[key] << fileStream.rdbuf();
            shaderStr[key] = shaderSS[key].str();

            fileStream.close();
        }

        const char* vertexSource = shaderStr["VERTEX"].c_str();
        const char* fragmentSource = shaderStr["FRAGMENT"].c_str();

        uint32_t vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertexSource, nullptr);
        glCompileShader(vertex);

        uint32_t fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragmentSource, nullptr);
        glCompileShader(fragment);

        shader.ProgramID = glCreateProgram();

        glAttachShader(shader.ProgramID, vertex);
        glAttachShader(shader.ProgramID, fragment);
        glLinkProgram(shader.ProgramID);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        return shader;

    }

    Shader ReloadShader(const Shader& shader, std::map<std::string, std::filesystem::path> paths)
    {
        Shader s;

        glDeleteProgram(shader.ProgramID);
        s = LoadShaders({
            { "VERTEX",     paths["VERTEX"] },
            { "FRAGMENT",   paths["FRAGMENT"] },
        });

        return s;
    }

    void UseShader(const Shader& shader)
    {
        glUseProgram(shader.ProgramID);
    }

    void SetShaderIntUniform(const Shader& shader, const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(shader.ProgramID, name.c_str()), value);
    }

    void SetShaderIntArrayUni(const Shader &shader, const std::string &name, size_t count, int value[])
    {
        glUniform1iv(glGetUniformLocation(shader.ProgramID, name.c_str()), count, value);
    }

    void SetShaderMat4Uniform(const Shader& shader, const std::string &name, const glm::mat4& value)
    {
        glUniformMatrix4fv(glGetUniformLocation(shader.ProgramID, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }
}