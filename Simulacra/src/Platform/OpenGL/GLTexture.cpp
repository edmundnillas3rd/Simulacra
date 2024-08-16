#include "GLTexture.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "src/Simulacra/Filesystem.h"

namespace Simulacra
{

    Texture LoadTexture(const std::string& path)
    {
        const std::string fullPath = FormatFilepathPlatform(path);
        Texture texture = { 0 };

        int n = 0;
        texture.Data = stbi_load(fullPath.c_str(), &texture.Width, &texture.Height, &n, 0);

        if (!texture.Data)
        {
            std::cout << "Error: Could not load " + path << std::endl;
        }
        
        GLenum internalFormat = 0, dataFormat = 0;
        if (n == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (n == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        stbi_set_flip_vertically_on_load(1);

        glCreateTextures(GL_TEXTURE_2D, 1, &texture.TextureID);
        glTextureStorage2D(texture.TextureID, 1, internalFormat, texture.Width, texture.Height);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTextureSubImage2D(texture.TextureID, 0, 0, 0, texture.Width, texture.Height, dataFormat, GL_UNSIGNED_BYTE, texture.Data);

        stbi_image_free(texture.Data);

        return texture;
    }

    Texture CreateTexture(int32_t width, int32_t height)
    {
        Texture texture = { 0 };
        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

        return texture;
    }

    Texture CreateImageTexture(int32_t width, int32_t height)
    {
        Texture texture = { 0 };
        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.TextureID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texture.Width, texture.Height, 0, GL_RGBA, GL_FLOAT, nullptr);

        glBindImageTexture(0, texture.TextureID, 0, GL_FALSE, 0, GL_READ_WRITE, GL_RGBA32F);

        return texture;
    }

    void SetActiveTexture(uint32_t index)
    {
        glActiveTexture(GL_TEXTURE0 + index);
    }

    void BindTexture(uint32_t slot, uint32_t texture)
    {
        glBindTextureUnit(slot, texture);
    }
}