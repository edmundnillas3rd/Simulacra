#include "Framebuffer.h"
#include <iostream>

#include <glad/glad.h>

#include "src/Simulacra/Window.h"

namespace Simulacra
{
    Framebuffer CreateFramebuffer(const std::string& name)
    {
        Framebuffer fbo;
        fbo.Name = name;
        
        glGenFramebuffers(1, &fbo.ID);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo.ID);

        return fbo;
    }

    void BindFramebuffer(uint32_t id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    Texture CreateTextureAttachment()
    {
        Texture texture;
        glGenTextures(1, &texture.TextureID);
        glBindTexture(GL_TEXTURE_2D, texture.TextureID);

        Window window = GetCurrentWindow();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.Width, window.Height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.TextureID, 0);

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            std::cout << "FRAMEBUFFER IS NOT COMPLETE" << std::endl;
        }
        return texture;
    }
}
