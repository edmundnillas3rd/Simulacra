#include "OpenGLShader.h"

#include <glad/glad.h>

#include <fstream>

#include "FileManager.h"
#include "Logger.h"

namespace Simulacra
{
    // NOTE(Edmund): Path should always be in this order when listed
    // [0]: Vertex Shader
    // [1]: Fragment Shader
    Shader LoadShaders(const std::vector<std::string>& paths)
    {
        Shader shader;
        static const uint8_t MAX_SHADER_STAGES = 5;

        auto ext = std::filesystem::path(paths[0]);
        if (ext.extension() != ".vert")
        {
            ConsoleError("Invalid File Extension for shaders");
            ConsoleError("Invalid path name: {}", paths[0]);
            return {};
        }

        std::stringstream shaderSS[MAX_SHADER_STAGES];
        std::string shaderStr[MAX_SHADER_STAGES];
        std::fstream fileStream;

        for (size_t i = 0; i < paths.size(); i++)
        {
            fileStream.open(FormatFilepath(paths[i]), std::ios::in | std::ios::binary);

            shaderSS[i] << fileStream.rdbuf();
            shaderStr[i] = shaderSS[i].str();

            fileStream.close();

        }

        enum SHADER_TYPE : uint32_t
        {
            VERTEX = 0,
            FRAGMENT = 1,
        };

        const char* vertexSource = shaderStr[SHADER_TYPE::VERTEX].c_str();
        const char* fragmentSource = shaderStr[SHADER_TYPE::FRAGMENT].c_str();

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

    void UseShader(const Shader& shader)
    {
        glUseProgram(shader.ProgramID);
    }

    void SetShaderIntUniform(const Shader& shader, const std::string &name, int value)
    {
        glUniform1i(glGetUniformLocation(shader.ProgramID, name.c_str()), value);
    }
}