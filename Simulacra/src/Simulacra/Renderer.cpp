#include "Renderer.h"

#include <glad/glad.h>

#include "Platform/OpenGL/Shader.h"

namespace Simulacra
{

    GLuint s_VAO;

    Shader s_Shader;

    void InitializeRenderer()
    {
        s_VAO = 0;

        s_Shader = LoadShaders("assets/shaders/default-screen.glsl");
        glCreateVertexArrays(1, &s_VAO);
        glBindVertexArray(s_VAO);
    }

    void RenderTexture(Texture texture)
    {

    }

    void DrawLine()
    {
        static float currentTime;
        currentTime += 1.0f * 0.05f;
        const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f, 1.0f };

        glClearBufferfv(GL_COLOR, 0, color);
        glPointSize(40.0f);
        SetActiveShader(s_Shader.Program);
        glDrawArrays(GL_POINTS, 0, 1);
    }
}