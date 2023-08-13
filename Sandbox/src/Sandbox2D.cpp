#include "Sandbox2D.h"

#include <math.h>

Sandbox2D::Sandbox2D()
{
    m_Shader = Simulacra::LoadShader({
        "assets/shaders/default.glsl",
        "assets/shaders/user-define.glsl"
    });

    glCreateVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    static float currentTime;

    currentTime += 1.5f * deltaTime;
    GLfloat attrib[] = { 
        (float)sin(currentTime) * 0.5f,
        (float)cos(currentTime) * 0.6f,
        0.0f, 
        0.0f 
    };

    GLfloat bg[] = {
        0.2f, 
        0.2f,
        0.2f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, bg);

    glUseProgram(m_Shader.IDs[1]);
    glVertexAttrib4fv(0, attrib);
    glVertexAttrib4fv(1, attrib);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Sandbox2D::OnRender()
{
}

void Sandbox2D::OnEvent(Simulacra::Event event)
{
}
