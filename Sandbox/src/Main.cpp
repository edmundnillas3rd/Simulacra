#include <Simulacra.h>
#include <imgui.h>
#include <glm/glm.hpp>

class Game : public Simulacra::Application
{
public:
    Game()
        : m_WindowFlags(0), m_Modified(false), m_Shaders({0})
    {
        Simulacra::Application::Config config;
        config.Title                                    = "Sandbox";
        config.Width                                    = 1280;
        config.Height                                   = 640;
        config.WorkingDirectory                         = "../../..";

        if (Create(config))
        {
            Run();
        }
    }

    ~Game()
    {

    }

public:
    virtual void OnStart() override
    {
        m_WindowFlags |= ImGuiWindowFlags_MenuBar;

        m_Shaders = Simulacra::LoadShaders({ 
            { "VERTEX",     "Sandbox/assets/shaders/main.vert" },
            { "FRAGMENT",   "Sandbox/assets/shaders/main.frag" }
        });

        Simulacra::WatchDirectory("Sandbox/assets/shaders", [this](void) -> void {
            m_Modified = true;
        });
    }

    virtual void OnUpdate(float delta) override
    {
        if (m_Modified)
        {
            m_Shaders = Simulacra::ReloadShader(m_Shaders);
            m_Modified = false;
        }

        Simulacra::BeginRender(m_Shaders);
            glm::mat4 t = glm::mat4(1.0f);
            Simulacra::DrawVertices(t);
        Simulacra::EndRender();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::ShowDemoWindow();

        if (!ImGui::Begin("Task Window", nullptr, m_WindowFlags))
        {
            ImGui::End();
            return;
        }


        ImGui::End();
    }

    virtual void OnEvent(Simulacra::Event event) override
    {
        if (event.Type == Simulacra::EventType::KEY_PRESSED_UP && event.Key == Simulacra::VKEY::SCANCODE_F5)
        {
            m_Shaders = Simulacra::ReloadShader(m_Shaders);
        }
    }

private:
    bool m_Modified;
    ImGuiWindowFlags m_WindowFlags;
    Simulacra::Shader m_Shaders;
};

int main()
{
    Game game;

    return 0;
}