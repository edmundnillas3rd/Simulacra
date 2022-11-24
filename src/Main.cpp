#include "Simulacra.h"

class Application : public Simulacra
{
public:
    Application()
        : vertices {
             0.0f,  0.5f, 1.0f,
             0.5f, -0.5f, 1.0f,
            -0.5f, -0.5f, 1.0f
        }
    {
        std::cout << "Application Object Created" << std::endl;

        shader.ID = LoadShader("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");

        bufferLayout.VAO = CreateBufferLayout();
        buffer.VBO = CreateBuffer();
        BindBufferLayout(bufferLayout.VAO);
        BindBuffer(buffer.VBO);
        SetBuffer(vertices, sizeof(vertices));

        SetBufferLayout(0, 3, 3 * sizeof(float), (void*)0);
        EnableVAByIndex(0);

    }

    ~Application()
    {
        std::cout << "Application Object Destroyed" << std::endl;
    }

    virtual void OnUpdate(float deltaTime) override
    {
        // std::cout << "Updating..." << std::endl;
        UseShader(shader.ID);
        BindBufferLayout(bufferLayout.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    virtual void OnEvent() override
    {
        // std::cout << "Polling Events..." << std::endl;
    }

private:
    float vertices[9];
    Buffer buffer;
    BufferLayout bufferLayout;
    Shader shader;
};

Simulacra* CreateApplication()
{
    return new Application();
}