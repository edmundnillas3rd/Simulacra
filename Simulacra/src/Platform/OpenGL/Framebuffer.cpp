#include "Framebuffer.h"

#include "src/Core/Window.h"
#include "src/Core/Log.h"

namespace Simulacra
{
    Framebuffer CreateFramebuffer()
    {
        Framebuffer buffer;

        glCreateFramebuffers(1, &buffer.ID);
        glBindFramebuffer(GL_FRAMEBUFFER, buffer.ID);

        glGenTextures(1, &buffer.ColorBuffer);
        glBindTexture(GL_TEXTURE_2D, buffer.ColorBuffer);

        Window window = GetWindowSize();
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, window.width, window.height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer.ColorBuffer, 0);

        glGenRenderbuffers(1, &buffer.RenderBuffer);
        glBindRenderbuffer(GL_RENDERBUFFER, buffer.RenderBuffer);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, window.width, window.height);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, buffer.RenderBuffer);

        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            SIM_LOG_ERROR("Failed to set framebuffer");
        }
        else
        {
            SIM_LOG_INFO("Successfully set framebuffer");
        }

        return buffer;
    }

    void BindFramebuffer(GLuint id)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, id);
    }

    void UnBindFramebuffer()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}