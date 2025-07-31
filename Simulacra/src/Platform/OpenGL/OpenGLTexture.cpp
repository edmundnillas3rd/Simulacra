#include "OpenGLTexture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glad/glad.h>

namespace Simulacra
{
    Texture CreateTexture()
    {
        Texture texture = {};

        glGenTextures(1, &texture.TextureID);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        texture.Width = 1;
        texture.Height = 1;

        glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA8, texture.Width, texture.Height);

        return texture;
    }

    Texture LoadTexture(const std::string& path)
    {
        Texture texture = {};

        glGenTextures(1, &texture.TextureID);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        int n = 0;
        texture.Data = stbi_load(path.c_str(), &texture.Width, &texture.Height, &n, 0);

        stbi_set_flip_vertically_on_load(1);

        GLenum format = 0, dataFormat = 0;
        
        if (n == 4)
        {
            dataFormat = GL_RGBA8;
            format = GL_RGBA;
        }
        else
        {
            dataFormat = GL_RGB8;
            format = GL_RGB;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, dataFormat, texture.Width, texture.Height, 0, format, GL_UNSIGNED_BYTE, texture.Data);

        return texture;
    }

    void BindTexture(const Texture& texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);
    }

    void SetActiveTexture(uint32_t index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    void WriteTexture(Texture& texture, void* data)
    {
        // TODO(Edumund): Add condition check for dynamic format RBGA and RBG;
        uint32_t dataFormat = GL_RGBA;

        glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, texture.Width, texture.Height, dataFormat, GL_UNSIGNED_BYTE, data);
    }
}