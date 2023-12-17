#include "Shader.h"

#include "src/Core/Log.h"
#include "src/Platform/Linux/FileSystem.h"

namespace Simulacra
{
    struct ShaderSource
    {
        std::string vertex;
        std::string tessellationCtrl;
        std::string tessellationEval;
        std::string geometry;
        std::string fragment;
    };

    static ShaderSource ParseShaderFile(const std::string& shaderSource);
    static void GetCompileStatus(GLuint program, GLenum type);
    static void GetLinkingStatus(GLuint program);

    Shader LoadShader(std::vector<std::string> paths)
    {
        Shader shader;

        const size_t PATH_SIZE = paths.size();
        std::vector<std::string> source(PATH_SIZE, " ");

        for (size_t pathIndex = 0; pathIndex < paths.size(); pathIndex++)
        {
            std::string shaderSource;
            std::ifstream shaderSourceFile;

            std::string shaderPath = filesystem.cwd + paths[pathIndex];

            shaderSourceFile.open(shaderPath.c_str(), std::ios::in);

            if (!shaderSourceFile.is_open())
                SIM_LOG_ERROR("Unable to locate shader file!");

            SIM_LOG_INFO("Reading shader file from {} ", paths[pathIndex]);
            while (getline(shaderSourceFile, shaderSource))
            {
                // source.push_back(shaderSource + '\n');
                source[pathIndex].append(shaderSource + '\n');

                // source[pathIndex] += shaderSource;
                // source[pathIndex].push_back('\n');
            }

            shaderSourceFile.close();

            ShaderSource src = ParseShaderFile(source[pathIndex]);

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

            // Tessellation
            GLuint tsc = 0;
            GLuint tse = 0;
            bool tessellation = !src.tessellationCtrl.empty() && !src.tessellationEval.empty();
            if (tessellation)
            {
                const GLchar* tessellationCtrlShaderSource = src.tessellationCtrl.c_str();
                tsc = glCreateShader(GL_TESS_CONTROL_SHADER); 
                glShaderSource(tsc, 1, &tessellationCtrlShaderSource, nullptr);
                glCompileShader(tsc);

                GetCompileStatus(tsc, GL_TESS_CONTROL_SHADER);
                glAttachShader(shader.IDs[pathIndex], tsc);

                const GLchar* tessellationEvalShaderSource = src.tessellationEval.c_str();
                tse = glCreateShader(GL_TESS_EVALUATION_SHADER); 
                glShaderSource(tse, 1, &tessellationEvalShaderSource, nullptr);
                glCompileShader(tse);

                GetCompileStatus(tse, GL_TESS_EVALUATION_SHADER);
                glAttachShader(shader.IDs[pathIndex], tse);
            }

            // Geometry
            GLuint gs = 0;
            bool geometry = !src.geometry.empty();
            if (geometry)
            {
                const GLchar* geometryShaderSource = src.geometry.c_str();
                gs = glCreateShader(GL_GEOMETRY_SHADER);
                glShaderSource(gs, 1, &geometryShaderSource, nullptr);
                glCompileShader(gs);

                GetCompileStatus(gs, GL_GEOMETRY_SHADER);
                glAttachShader(shader.IDs[pathIndex], gs);
            }

            glAttachShader(shader.IDs[pathIndex], fs);

            glLinkProgram(shader.IDs[pathIndex]);
            GetLinkingStatus(shader.IDs[pathIndex]);

            glDeleteShader(vs);

            if (tessellation)
            {
                glDeleteShader(tsc);
                glDeleteShader(tse);
            }

            if (geometry)
                glDeleteShader(gs);

            glDeleteShader(fs);

        }

        return shader;
    }

    void SetShaderMat4(GLuint program, const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

    void SetShaderInt(GLuint program, const std::string &name, int value)
    { 
        glUniform1i(glGetUniformLocation(program, name.c_str()), value); 
    }

    static ShaderSource ParseShaderFile(const std::string& shaderSource)
    {
        std::string shaderStr;
        std::stringstream ss(shaderSource);
        std::stringstream shaderSS[5];

        enum class ShaderType 
        {
            NONE = -1,
            VERTEX = 0,
            TESSELLATION_CTRL = 1,
            TESSELLATION_EVAL = 2,
            GEOMETRY = 3,
            FRAGMENT = 4
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
                else if (shaderStr.find("tessellation-control") != std::string::npos)
                {
                    type = ShaderType::TESSELLATION_CTRL;
                }
                else if (shaderStr.find("tessellation-evaluation") != std::string::npos)
                {
                    type = ShaderType::TESSELLATION_EVAL;
                }
                else if (shaderStr.find("geometry") != std::string::npos)
                {
                    type = ShaderType::GEOMETRY;
                }
                else if (shaderStr.find("fragment") != std::string::npos)
                {
                    type = ShaderType::FRAGMENT;
                }
                else
                {
                    type = ShaderType::NONE;
                }
            }
            else
            {
                shaderSS[(int)type] << shaderStr << "\n";
            }
        }

        return { 
            shaderSS[0].str(), 
            shaderSS[1].str(), 
            shaderSS[2].str(),
            shaderSS[3].str(),
            shaderSS[4].str()
        };
    }

    static void GetCompileStatus(GLuint program, GLenum type)
    {
        std::string shader = type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT";

        if (type == GL_TESS_CONTROL_SHADER || type == GL_TESS_EVALUATION_SHADER)
        {
            std::string prefix = type == GL_TESS_CONTROL_SHADER ? "CONTROL" : "EVALUATION";
            shader = "TESSELATION " + prefix;
        }
        else if (type == GL_GEOMETRY_SHADER)
        {
            shader = "GEOMETRY";
        }

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

            std::string msg(logLength, ' ');
            glGetShaderInfoLog(program, logLength, nullptr, (char*)msg.c_str());

            std::string fmtMsg = msg;
            SIM_LOG_ERROR("{} COMPILE ERROR: \n{}", shader, fmtMsg);
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

            std::string msg(logLength, ' ');
            glGetProgramInfoLog(program, logLength, nullptr, (char*)msg.c_str());

            std::string fmtMsg = msg;
            SIM_LOG_ERROR("LINKING ERROR: \n{}", fmtMsg);
        }
    }
}