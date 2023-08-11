#include "Shader.h"

namespace Simulacra
{
    struct ShaderSource
    {
        std::string vertex;
        std::string fragment;
    };

    static ShaderSource SplitShaderFile(const std::string& shaderSource);

    void LoadShader(std::vector<std::string> paths)
    {
        std::string source;
        for (const auto& path : paths)
        {
            std::string shaderSource;
            std::ifstream shaderSourceFile;

            shaderSourceFile.open(path.c_str(), std::ios::in);

            if (!shaderSourceFile.is_open())
                std::cout << "Unable to locate file\n";

            while (getline(shaderSourceFile, shaderSource))
            {
                source += shaderSource;
                source.push_back('\n');
            }

            shaderSourceFile.close();
        }

        ShaderSource src = SplitShaderFile(source);

        src.vertex;
        src.fragment;
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