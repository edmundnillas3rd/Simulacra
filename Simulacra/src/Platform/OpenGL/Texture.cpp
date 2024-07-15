#include "Texture.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "src/Simulacra/Filesystem.h"

namespace Simulacra
{

    Texture LoadTexture(const std::string& path)
    {
        const std::string fullPath = FileManager.CurrenWorkingDirectory + path;
        Texture texture;

        int n = 0;
        int forceChannels = 4;
        unsigned char* imageData = stbi_load(fullPath.c_str(), &texture.Size.x, &texture.Size.y, &n, forceChannels);
        if (!imageData)
        {
            std::cout << "Error: Could not load " + path << std::endl;
        }

        stbi_set_flip_vertically_on_load(1);

        glGenTextures(1, &texture.TextureID);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Size.x, texture.Size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(imageData);

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