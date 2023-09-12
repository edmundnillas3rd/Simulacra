#include "Framebuffer.h"

#include "src/Core/Log.h"

namespace Simulacra
{
    Framebuffer CreateFramebuffer()
    {
        Framebuffer buffer;

        GLuint FBO;
        glCreateFramebuffers(1, &FBO);
        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        buffer.ID = FBO;
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        return buffer;
    }

    void AttackTextureToFramebuffer(GLuint buffer)
    {
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, buffer, 0);
        if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        {
            SIM_LOG_ERROR("Failed to set framebuffer");
        }
    }
}