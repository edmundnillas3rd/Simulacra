#include "Shader.h"

#include <fstream>
#include <sstream>

namespace Simulacra
{
    std::array<std::string, 5> ParseShader(const std::string& source);

    Shader LoadShaders(const std::string &path)
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
        glShaderSource(vs, 1, &vertex, NULL);
        glCompileShader(vs);

        int params = -1;
        glGetShaderiv(vs, GL_COMPILE_STATUS, &params);
        if(params != GL_TRUE) 
        {
            std::cout << "GL Shader Vertex did not compile: " << vs << std::endl;
            return shader;
        }
        
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &fragment, NULL);
        glCompileShader(fs);

        params = -1;
        glGetShaderiv(fs, GL_COMPILE_STATUS, &params);
        if(params != GL_TRUE) 
        {
            std::cout << "GL Shader Fragment did not compile: " << fs << std::endl;
            return shader;
        }

        shader.Program = glCreateProgram();
        glAttachShader(shader.Program, vs);
        glAttachShader(shader.Program, fs);
        glLinkProgram(shader.Program);

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

    void SetIntShader(const std::string& location, int i, int j)
    {
    }

    void SetIntShader(const std::string& location, int i)
    {
    }
}