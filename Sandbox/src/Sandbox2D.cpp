#include "Sandbox2D.h"

Sandbox2D::Sandbox2D()
{
    m_Shader = Simulacra::LoadShader({
        "assets/shaders/default.glsl",          // m_Shader.IDs[0]
        "assets/shaders/user-define.glsl"       // m_Shader.IDs[1]
    });

    // Should be read in clockwise
    // float vertices[] = {
    //     -1.0f, -1.0f, 0.0f, 1.0f,
    //      1.0f, -1.0f, 0.0f, 1.0f,
    //      1.0f,  1.0f, 0.0f, 1.0f,
    //     -1.0f,  1.0f, 0.0f, 1.0f        
    // };

    glCreateVertexArrays(1, &m_VAO);
    // glCreateBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    // glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_STATIC_DRAW);

    // glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);

    // glEnableVertexAttribArray(0);
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    static float currentTime;
    const float SPEED = 1.5f;

    currentTime += SPEED * deltaTime;
    GLfloat attrib[] = { 
        (float)sin(currentTime) * 0.5f,
        (float)cos(currentTime) * 0.6f,
        0.0f, 
        0.0f 
    };

    GLfloat bg[] = {
        0.05f, 
        0.05f,
        0.25f,
        1.0f
    };

    glClearBufferfv(GL_COLOR, 0, bg);

    glUseProgram(m_Shader.IDs[1]);
    glVertexAttrib4fv(0, attrib);
    glVertexAttrib4fv(1, attrib);
    glBindVertexArray(m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Sandbox2D::OnRender()
{
}

void Sandbox2D::OnEvent(Simulacra::Event event)
{
}
