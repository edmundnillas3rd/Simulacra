#include <Simulacra.h>
#include <imgui.h>

class Game : public Simulacra::Application
{
public:
    Game()
        : m_WindowFlags(0)
    {

    }

    ~Game()
    {

    }

    virtual void OnStart() override
    {
        m_WindowFlags |= ImGuiWindowFlags_MenuBar;

        m_Shaders = Simulacra::LoadShaders({ 
            { "VERTEX",     "Sandbox/assets/shaders/main.vert" },
            { "FRAGMENT",   "Sandbox/assets/shaders/main.frag" }
        });
    }

    virtual void OnUpdate(float delta) override
    {
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

private:
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