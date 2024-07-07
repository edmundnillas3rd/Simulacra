#include "Renderer.h"

#include <glad/glad.h>

#include "Platform/OpenGL/Shader.h"

namespace Simulacra
{

    Renderer* s_Renderer;

    Renderer* CreateRenderer();

    GLuint VAO;

    static Shader shader;

    void InitializeRenderer()
    {
        s_Renderer = nullptr;
        VAO = 0;

        shader = LoadShaders("assets/shaders/default-screen.glsl");
        glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
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
        SetActiveShader(shader.Program);
        glDrawArrays(GL_POINTS, 0, 1);
    }

    Renderer* CreateRenderer()
    {
        Renderer renderer;
        return nullptr;
    }

}