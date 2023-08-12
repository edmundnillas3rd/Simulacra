#include "Shader.h"

#include "Log.h"

namespace Simulacra
{
    struct ShaderSource
    {
        std::string vertex;
        std::string fragment;
    };

    static ShaderSource SplitShaderFile(const std::string& shaderSource);

    Shader LoadShader(std::vector<std::string> paths)
    {
        Shader shader;

        const size_t PATH_SIZE = paths.size();
        std::string source[PATH_SIZE];

        for (size_t pathIndex = 0; pathIndex < paths.size(); pathIndex++)
        {
            std::string shaderSource;
            std::ifstream shaderSourceFile;

            shaderSourceFile.open(paths[pathIndex].c_str(), std::ios::in);

            if (!shaderSourceFile.is_open())
                SIM_LOG_ERROR("Unable to locate shader file!");

            while (getline(shaderSourceFile, shaderSource))
            {
                source[pathIndex] += shaderSource;
                source[pathIndex].push_back('\n');
            }

            shaderSourceFile.close();

            ShaderSource src = SplitShaderFile(source[pathIndex]);

            const GLchar* vertexShaderSource[] = {
                src.vertex.c_str()
            };

            const GLchar* fragmentShaderSource[] = {
                src.fragment.c_str()
            };

            // Vertex
            GLuint vs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vs, 1, vertexShaderSource, nullptr);
            glCompileShader(vs);

            // Fragment
            GLuint fs = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(fs, 1, fragmentShaderSource, nullptr);
            glCompileShader(fs);

            shader.IDs.push_back(glCreateProgram());
            glAttachShader(shader.IDs[pathIndex], vs);
            glAttachShader(shader.IDs[pathIndex], fs);
            glLinkProgram(shader.IDs[pathIndex]);

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
}