#include "src/Simulacra/Renderer.h"

#include <array>

#include <glad/glad.h>

namespace Simulacra
{
    void DrawIndices(Shader shader, VertexArrayBuffer object, uint32_t count)
    {
        SetActiveShader(shader.ProgramID);
        BindVertexArrayBuffer(object.RendererID);
        glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
    }
}