#include "Simulacra.h"

class Application : public Simulacra
{
public:
    Application()
    {
        std::cout << "Application Object Created" << std::endl;

        float vertices[] =  {
             0.0f,  0.5f, 1.0f, 0.5f, 1.0f,
             0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 1.0f, 1.0f, 0.0f
        };

        unsigned int indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        shader.ID = LoadShader("assets/shaders/vertex.vs", "assets/shaders/fragment.fs");

        bufferLayout.VAO = CreateBufferLayout();
        buffer.VBO = CreateBuffer();
        BindBufferLayout(bufferLayout.VAO);

        BindBuffer(buffer.VBO);
        SetBuffer(vertices, sizeof(vertices));

        SetBufferLayout(0, 3, 5 * sizeof(float), (void*)0);
        EnableVAByIndex(0);

        SetBufferLayout(1, 2, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        EnableVAByIndex(1);

        texture.ID = CreateTexture();
        BindTexture(texture.ID);

        SetTextureParams(GL_TEXTURE_WRAP_S, GL_REPEAT);
        SetTextureParams(GL_TEXTURE_WRAP_T, GL_REPEAT);
        SetTextureParams(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        SetTextureParams(GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        LoadTexture("assets/images/wall.jpg");
        UseShader(shader.ID);
        SetUniformInt(shader.ID, "texture1", 0);
    }

    ~Application()
    {
        std::cout << "Application Object Destroyed" << std::endl;
    }

    virtual void OnUpdate(float deltaTime) override
    {
        // std::cout << "Updating..." << std::endl;

        glActiveTexture(GL_TEXTURE0);
        BindTexture(texture.ID);
        UseShader(shader.ID);
        BindBufferLayout(bufferLayout.VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

    virtual void OnEvent() override
    {
        // std::cout << "Polling Events..." << std::endl;
    }

private:
    Buffer buffer;
    BufferLayout bufferLayout;
    Texture texture;
    Shader shader;
};

Simulacra* CreateApplication()
{
    return new Application();
}