#include "Sandbox2D.h"

#include <SDL.h>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
    : m_FreeRoam(false)
{
    m_Shader = Simulacra::LoadShader({
        "assets/shaders/default.glsl",          // m_Shader.IDs[0]
        "assets/shaders/default-screen.glsl"    // m_Shader.IDs[1]
    });

    float cubeVertices[] = {
        // positions          // texture Coords
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    float quadVertices[] = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
        // positions   // texCoords
        -1.0f,  1.0f,  0.0f, 1.0f,
        -1.0f, -1.0f,  0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 0.0f,

        -1.0f,  1.0f,  0.0f, 1.0f,
         1.0f, -1.0f,  1.0f, 0.0f,
         1.0f,  1.0f,  1.0f, 1.0f
    };

    Simulacra::Window window = Simulacra::GetWindowSize();

    lastX = (float)window.width / 2.0;
    lastY = (float)window.height / 2.0;

    // Cube
    glGenVertexArrays(1, &m_CubeVAO);
    glGenBuffers(1, &m_CubeVBO);
    glBindVertexArray(m_CubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_CubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // Screen Quad
    glGenVertexArrays(1, &m_QuadVAO);
    glGenBuffers(1, &m_QuadVBO);
    glBindVertexArray(m_QuadVAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_QuadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    m_Texture = Simulacra::LoadTexture("assets/images/container.jpg");

    glUseProgram(m_Shader.IDs[0]);
    Simulacra::SetShaderInt(m_Shader.IDs[0], "texture1", 0);

    glUseProgram(m_Shader.IDs[1]);
    Simulacra::SetShaderInt(m_Shader.IDs[1], "screenTexture", 0);

    // Framebuffer
    m_FBO = Simulacra::CreateFramebuffer();
    Simulacra::UnBindFramebuffer();

    glEnable(GL_DEPTH_TEST);

}

Sandbox2D::~Sandbox2D()
{
    glDeleteBuffers(1, &m_CubeVBO);
    glDeleteVertexArrays(1, &m_CubeVAO);

    glDeleteBuffers(1, &m_QuadVBO);
    glDeleteVertexArrays(1, &m_QuadVAO);

    glDeleteFramebuffers(1, &m_FBO.ID);
}

void Sandbox2D::OnUpdate(float deltaTime)
{
    Simulacra::BindFramebuffer(m_FBO.ID);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    if (m_FreeRoam)
    {
        // Mouse Movement
        int x, y;
        SDL_GetMouseState(&x, &y);
        float xpos = static_cast<float>(x);
        float ypos = static_cast<float>(y);
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos;

        lastX = xpos;
        lastY = ypos;

        m_Camera.ProcessMouseMovement(xoffset, yoffset);

        // Camera Movement
        if (Simulacra::IsKeyPressed(Simulacra::VKEY::KEY_W))
        {
            m_Camera.ProcessKeyboard(Simulacra::FORWARD, deltaTime);
        }
        else if (Simulacra::IsKeyPressed(Simulacra::VKEY::KEY_S))
        {
            m_Camera.ProcessKeyboard(Simulacra::BACKWARD, deltaTime);
        }

        if (Simulacra::IsKeyPressed(Simulacra::VKEY::KEY_A))
        {
            m_Camera.ProcessKeyboard(Simulacra::LEFT, deltaTime);
        }
        else if (Simulacra::IsKeyPressed(Simulacra::VKEY::KEY_D))
        {
            m_Camera.ProcessKeyboard(Simulacra::RIGHT, deltaTime);
        }
    }

    glUseProgram(m_Shader.IDs[0]);
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = m_Camera.GetViewMatrix();

    Simulacra::Window window = Simulacra::GetWindowSize();
    glm::mat4 projection = glm::perspective(glm::radians(m_Camera.Zoom), (float)window.width / (float)window.height, 0.1f, 100.0f);

    Simulacra::SetShaderMat4(m_Shader.IDs[0], "view", view);
    Simulacra::SetShaderMat4(m_Shader.IDs[0], "projection", projection);

    // Draw Scene
    for (const auto& object : Simulacra::MainScene.GameObjects)
    {
        switch (object.Type)
        {
        case Simulacra::Shape3D::CUBE:
            glBindVertexArray(m_CubeVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_Texture.ID);

            model = glm::mat4(1.0f);
            model = glm::translate(model, object.Position);
            model = glm::rotate(model, 90.0f, glm::vec3(object.Rotation));
            model = glm::scale(model, object.Scale);
            Simulacra::SetShaderMat4(m_Shader.IDs[0], "model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            glBindVertexArray(0);

            break;
        default:
            break;
        }
    }

    // glBindVertexArray(m_CubeVAO);
    // glActiveTexture(GL_TEXTURE0);
    // glBindTexture(GL_TEXTURE_2D, m_Texture.ID);

    // model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
    // Simulacra::SetShaderMat4(m_Shader.IDs[0], "model", model);
    // glDrawArrays(GL_TRIANGLES, 0, 36);

    // model = glm::mat4(1.0f);
    // model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
    // Simulacra::SetShaderMat4(m_Shader.IDs[0], "model", model);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    // glBindVertexArray(0);
    
    Simulacra::UnBindFramebuffer();
    // glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    // glClear(GL_COLOR_BUFFER_BIT);

    // glUseProgram(m_Shader.IDs[1]);
    // glBindVertexArray(m_QuadVAO);
    // glDisable(GL_DEPTH_TEST);
    // glBindTexture(GL_TEXTURE_2D, m_ColorBuffer);
    // glDrawArrays(GL_TRIANGLES, 0, 6); 
}

void Sandbox2D::OnImGuiRender()
{
    // ImGui::ShowDemoWindow();

    ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

    ImGuiWindowClass windowClass;
    windowClass.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_AutoHideTabBar;
    windowClass.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_PassthruCentralNode;
    ImGui::SetNextWindowClass(&windowClass);

    // Editor
    ImGuiWindowFlags windowFlags = 0;
    windowFlags |= ImGuiWindowFlags_NoTitleBar;
    ImGui::Begin("Scene Manager", nullptr, windowFlags);

    // Scene
    ImGui::SeparatorText("Scene");

    static ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    
    int n = 1;
    if (ImGui::TreeNode((void*)(intptr_t)n, "MainScene"))
    {
        int nodeClicked = -1;
        static int selectionMask = (1 << 2);
        for (size_t count = 0; count < Simulacra::MainScene.GameObjects.size(); count++)
        {
            ImGuiTreeNodeFlags nodeFlags = baseFlags;
            const bool selected = (selectionMask & (1 << count)) != 0;
            if (selected)
            {
                nodeFlags |= ImGuiTreeNodeFlags_Selected;
            }

            bool open = ImGui::TreeNodeEx((void*)(intptr_t)count, nodeFlags, Simulacra::MainScene.GameObjects[count].Name.c_str());

            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
            {
                nodeClicked = count;
                Simulacra::MainScene.SelectedGameObject = &Simulacra::MainScene.GameObjects[count];
            }

            // TODO: might populated children node
            if (open)
            {
                ImGui::TreePop();
            }
        }

        if (nodeClicked != -1)
        {
            if (ImGui::GetIO().KeyCtrl)
            {
                selectionMask ^= (1 << nodeClicked);
                Simulacra::MainScene.SelectedGameObject = nullptr;
            }
            else
            {
                selectionMask = (1 << nodeClicked);  
            }
        }

        ImGui::TreePop();
    }

    ImGui::Checkbox("Enable Free Roam", &m_FreeRoam);

    float windowSizeOffsetY = ImGui::GetWindowSize().y * 0.5;
    ImGui::Dummy(ImVec2(0.0f, windowSizeOffsetY));

    ImGui::SeparatorText("Inspector");
    auto* gameObject = Simulacra::MainScene.SelectedGameObject;

    if (gameObject)
    {
        ImGui::SliderFloat3("Translate", glm::value_ptr(gameObject->Position), -100.0f, 100.0f);
        ImGui::SliderFloat3("Rotate", glm::value_ptr(gameObject->Rotation), -100.0f, 100.0f);
        ImGui::SliderFloat3("Scale", glm::value_ptr(gameObject->Scale), 0.0f, 1.0f);

        Simulacra::UpdateScene();
    }


    windowSizeOffsetY = 20.0f;
    ImGui::Dummy(ImVec2(0.0f, windowSizeOffsetY));

    ImGui::SeparatorText("Components");
    ImGui::Spacing();

    if (ImGui::Button("+ Add GameObject"))
    {
        ImGui::OpenPopup("gameobject_popup");
    }

    if (ImGui::BeginPopup("gameobject_popup", ImGuiWindowFlags_NoMove))
    {
        ImGui::SeparatorText("Add Game Objects");
        if (ImGui::Button("Cube"))
        {
            Simulacra::AddGameObject("Cube");
        }
        ImGui::Button("Sphere");
        ImGui::Button("Plane");
        ImGui::EndPopup();
    }

    // Editor Viewport
    ImGui::Begin("Viewport", nullptr, windowFlags);
    ImVec2 windowSize = ImGui::GetWindowSize();
    ImGui::Image(reinterpret_cast<ImTextureID>(m_FBO.ColorBuffer), ImVec2(windowSize.x, windowSize.y), ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    ImGui::End();
}

void Sandbox2D::OnEvent(Simulacra::Event event)
{
}
