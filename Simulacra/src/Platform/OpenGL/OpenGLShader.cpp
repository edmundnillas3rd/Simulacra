#include "OpenGLShader.h"

#include <glad/glad.h>

#include "../../Platform/FileSystem.h"
#include "../../Core/Logger.h"

namespace Simulacra
{
    static uint32_t CreateAndLinkShaderProgram(std::map<std::string, uint32_t> shaders);
    static uint32_t CompileShader(const char* shaderSource, const std::string& shaderType);

    Shader LoadShaders(const std::map<std::string, std::filesystem::path>& paths)
    {
        Shader shader;

        std::map<std::string, std::stringstream> shaderSS;
        std::map<std::string, std::string> shaderStr;
        std::fstream fileStream;

        for (const auto& [key, value] : paths)
        {
            shader.Filepaths[key] = value;

            fileStream.open(FormatFilepath(value), std::ios::in | std::ios::binary);

            shaderSS[key] << fileStream.rdbuf();
            shaderStr[key] = shaderSS[key].str();

            fileStream.close();
        }

        const char* vertexSource = shaderStr["VERTEX"].c_str();
        const char* fragmentSource = shaderStr["FRAGMENT"].c_str();

        uint32_t vertex = CompileShader(vertexSource, "VERTEX");
        uint32_t fragment = CompileShader(fragmentSource, "FRAGMENT");

        uint32_t program = glCreateProgram();
        glAttachShader(program, vertex);
        glAttachShader(program, fragment);
        glLinkProgram(program);

        glDeleteShader(vertex);
        glDeleteShader(fragment);

        shader.ProgramID = program;

        return shader;

    }

    uint32_t CompileShader(const char* shaderSource, const std::string& shaderType)
    {
        uint32_t shader = 0;
        if (shaderType == "VERTEX")                 shader = glCreateShader(GL_VERTEX_SHADER);
        else if (shaderType == "FRAGMENT")          shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);

        int compiled;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (compiled != GL_TRUE)
        {
            int length;
            char msg[2048];
            glGetShaderInfoLog(shader, 2048, &length, msg);
            SIMULACRA_ERROR("Failed to compile shader: {}", msg);
            return 0;
        }

        return shader;
    }

    Shader ReloadShader(Shader& shader)
    {
        Shader reloadedShader = LoadShaders(shader.Filepaths);

        if (reloadedShader.ProgramID)
        {
            glDeleteProgram(shader.ProgramID);
            return reloadedShader;
        }

        return {0};
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