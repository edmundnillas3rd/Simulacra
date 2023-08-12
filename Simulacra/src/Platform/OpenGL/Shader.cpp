#include "Shader.h"

#include "Log.h"
#include "src/Platform/Windows/FileSystem.h"

namespace Simulacra
{
    struct ShaderSource
    {
        std::string vertex;
        std::string fragment;
    };

    static ShaderSource SplitShaderFile(const std::string& shaderSource);
    static void GetCompileStatus(GLuint program, GLenum type);
    static void GetLinkingStatus(GLuint program);

    Shader LoadShader(std::vector<std::string> paths)
    {
        Shader shader;

        const size_t PATH_SIZE = paths.size();
        std::string source[PATH_SIZE];

        for (size_t pathIndex = 0; pathIndex < paths.size(); pathIndex++)
        {
            std::string shaderSource;
            std::ifstream shaderSourceFile;

            std::string shaderPath = filesystem.cwd + paths[pathIndex];

            shaderSourceFile.open(shaderPath.c_str(), std::ios::in);

            if (!shaderSourceFile.is_open())
                SIM_LOG_ERROR("Unable to locate shader file!");

            while (getline(shaderSourceFile, shaderSource))
            {
                source[pathIndex] += shaderSource;
                source[pathIndex].push_back('\n');
            }

            shaderSourceFile.close();

            ShaderSource src = SplitShaderFile(source[pathIndex]);

            const GLchar* vertexShaderSource = src.vertex.c_str();
            const GLchar* fragmentShaderSource = src.fragment.c_str();

            // Vertex
            GLuint vs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vs, 1, &vertexShaderSource, nullptr);
            glCompileShader(vs);

            GetCompileStatus(vs, GL_VERTEX_SHADER);

            // Fragment
            GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fs, 1, &fragmentShaderSource, nullptr);
            glCompileShader(fs);

            GetCompileStatus(fs, GL_FRAGMENT_SHADER);

            shader.IDs.push_back(glCreateProgram());
            glAttachShader(shader.IDs[pathIndex], vs);
            glAttachShader(shader.IDs[pathIndex], fs);
            glLinkProgram(shader.IDs[pathIndex]);

            GetLinkingStatus(shader.IDs[pathIndex]);

            glDeleteShader(vs);
            glDeleteShader(fs);
        }

        return shader;
    }

    static ShaderSource SplitShaderFile(const std::string& shaderSource)
    {
        std::string shaderStr;
        std::stringstream ss(shaderSource);
        std::stringstream shaderSS[2];

        enum class ShaderType 
        {
            NONE = -1,
            VERTEX = 0,
            FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;

        while (getline(ss, shaderStr))
        {
            if (shaderStr.find("#shader") != std::string::npos)
            {
                if (shaderStr.find("vertex") != std::string::npos)
                {
                    type = ShaderType::VERTEX;
                }
                else if (shaderStr.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
            }
            else
            {
                shaderSS[(int)type] << shaderStr << "\n";
            }
        }

        return { shaderSS[0].str(), shaderSS[1].str() };
    }

    static void GetCompileStatus(GLuint program, GLenum type)
    {
        std::string shader = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";
        GLint success = -1;
        glGetShaderiv(program, GL_COMPILE_STATUS, &success);
        if (success)
        {
            SIM_LOG_INFO("Successfully compile {} shader", shader);
        }
        else
        {
            GLint logLength;
            glGetShaderiv(program, GL_INFO_LOG_LENGTH, &logLength);

            char msg[logLength];
            glGetShaderInfoLog(program, logLength, nullptr, msg);

            std::string fmtMsg = msg;
            SIM_LOG_ERROR("{} COMPILE ERROR: \n{}", shader,fmtMsg);
        }
    }

    static void GetLinkingStatus(GLuint program)
    {
        GLint success = -1;
        glGetProgramiv(program, GL_LINK_STATUS, &success);

        if (success)
        {
            SIM_LOG_INFO("Successfully link shaders");
        }
        else
        {
            SIM_LOG_ERROR("Failed to link shaders");

            GLint logLength;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

            char msg[logLength];
            glGetProgramInfoLog(program, logLength, nullptr, msg);

            std::string fmtMsg = msg;
            SIM_LOG_ERROR("LINKING ERROR: \n{}", fmtMsg);
        }
    }
}