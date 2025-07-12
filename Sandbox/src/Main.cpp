#include <Simulacra.h>
#include <imgui.h>

class Game : public Simulacra::Application
{
public:
    Game()
        : m_WindowFlags(0), m_Modified(false), m_Shaders({0})
    {

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
            Simulacra::ReloadShader(m_Shaders);
            m_Modified = false;
        }

        Simulacra::BeginRender(m_Shaders);
            Simulacra::DrawVertices();
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

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Open", "CTRL-O"))
                {
                    Simulacra::ConsoleLog("Open Menu Item was clicked");
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }


        ImGui::End();
    }

    virtual void OnEvent(Simulacra::Event event) override
    {
        if (event.Type == Simulacra::EventType::KEY_PRESSED_UP && event.Key == Simulacra::VKEY::SCANCODE_F5)
        {
            Simulacra::ReloadShader(m_Shaders);
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
    if (game.CreateApplication({"The titled game", 1280, 680}))
        game.RunApplication();

    return 0;
}