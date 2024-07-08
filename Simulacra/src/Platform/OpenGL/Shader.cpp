#include "Shader.h"

#include <fstream>
#include <sstream>

namespace Simulacra
{
    std::array<std::string, 5> ParseShader(const std::string& source);

    Shader LoadShaders(const std::string& path)
    {
        std::fstream shaderFile(path.c_str(), std::ios::in | std::ios::binary);
        std::stringstream ss;

        ss << shaderFile.rdbuf();

        shaderFile.close();

        Shader shader;

        shader.Sources = ParseShader(ss.str());
        
        std::cout << shader.Sources[0] << std::endl;
        std::cout << shader.Sources[1] << std::endl;

        const char* vertex = shader.Sources[0].c_str();
        const char* fragment = shader.Sources[1].c_str();

        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &vertex, nullptr);
        glCompileShader(vs);

        int success = -1;
        char infoLog[512];
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if(success != GL_TRUE) 
        {
            glGetShaderInfoLog(vs, 512, nullptr, infoLog);
            std::cout << "VERTEX SHADER COMPILATION FAILED: " << infoLog << std::endl;
            return shader;
        }
        
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment, nullptr);
        glCompileShader(fs);

        success = -1;
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if(success != GL_TRUE) 
        {
            glGetShaderInfoLog(fs, 512, nullptr, infoLog);
            std::cout << "FRAGMENT SHADER COMPILATION FAILED: " << infoLog << std::endl;
            return shader;
        }

        shader.ProgramID = glCreateProgram();
        glAttachShader(shader.ProgramID, vs);
        glAttachShader(shader.ProgramID, fs);
        glLinkProgram(shader.ProgramID);

        glDeleteShader(vs);
        glDeleteShader(fs);

        return shader;
    }

    std::array<std::string, 5> ParseShader(const std::string& source)
    {
        std::string shaderStr;
        std::stringstream sources(source);
        std::array<std::stringstream, 5> shaderSources;

        int shaderIndex = -1;
        while (std::getline(sources, shaderStr))
        {
            if (shaderStr.find("#shader") != std::string::npos)
            {
                if (shaderStr.find("vertex") != std::string::npos)
                {
                    shaderIndex = 0;
                }
                else if (shaderStr.find("fragment") != std::string::npos)
                {
                    shaderIndex = 1;
                }
            }
            else
            {
                shaderSources[shaderIndex] << shaderStr;
            }
        }

        return {
            shaderSources[0].str(),
            shaderSources[1].str(),
            "",
            "",
            ""
        };
    }

    void SetActiveShader(GLuint program)
    {
        glUseProgram(program);
    }

    void SetIntUniform(const Shader& shader, const std::string& location, int i)
    {
        glUniform1i(glGetUniformLocation(shader.ProgramID, location.c_str()), i);
    }

    void SetIntUniform(const Shader& shader, const std::string& location, int i, int j)
    {
        glUniform2i(glGetUniformLocation(shader.ProgramID, location.c_str()), i, j);
    }

    void SetIntUniform(const Shader& shader, const std::string &location, int i, int j, int k)
    {
        glUniform3i(glGetUniformLocation(shader.ProgramID, location.c_str()), i, j, k);
    }

    void SetFloatUniform(const Shader& shader, const std::string &location, float i)
    {
        glUniform1f(glGetUniformLocation(shader.ProgramID, location.c_str()), i);
    }

    void SetFloatUniform(const Shader& shader, const std::string &location, float i, float j)
    {
        glUniform2f(glGetUniformLocation(shader.ProgramID, location.c_str()), i, j);
    }
    
    void SetFloatUniform(const Shader& shader, const std::string &location, float i, float j, float k)
    {
        glUniform3f(glGetUniformLocation(shader.ProgramID, location.c_str()), i, j, k);
    }
}