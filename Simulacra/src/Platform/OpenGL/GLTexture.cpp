#include "GLTexture.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "src/Simulacra/Filesystem.h"

namespace Simulacra
{

    Texture LoadTexture(const std::string& path)
    {
        const std::string fullPath = FileManager.CurrenWorkingDirectory + path;
        Texture texture = { 0 };

        int n = 0;
        int forceChannels = 4;
        texture.Data = stbi_load(fullPath.c_str(), &texture.Width, &texture.Height, &n, forceChannels);
        if (!texture.Data)
        {
            std::cout << "Error: Could not load " + path << std::endl;
        }

        stbi_set_flip_vertically_on_load(1);

        glGenTextures(1, &texture.TextureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture.Data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(texture.Data);

        return texture;
    }

    Texture CreateTexture(int32_t width, int32_t height)
    {
        Texture texture = { 0 };
        texture.Width = width;
        texture.Height = height;

        glGenTextures(1, &texture.TextureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

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

    void BindTexture(uint32_t texture)
    {
        glBindTexture(GL_TEXTURE_2D, texture);
    }
}