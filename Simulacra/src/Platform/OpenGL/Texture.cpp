#include "Texture.h"
#include <stb_image.h>

#include "src/Core/Window.h"
#include "src/Core/Log.h"
#include "src/Platform/Linux/FileSystem.h"

namespace Simulacra
{
    Texture LoadTexture(const std::string& path)
    {
        Texture texture;
        glGenTextures(1, &texture.ID);
        glBindTexture(GL_TEXTURE_2D, texture.ID); 

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);
        
        std::string formattedPath = path + filesystem.cwd;
        unsigned char *data = stbi_load(formattedPath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            SIM_LOG_ERROR("Failed to load texture");
        }
        stbi_image_free(data);
        
        return texture;
    }
}
