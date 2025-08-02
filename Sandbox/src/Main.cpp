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
        config.WorkingDirectory                         = "../../../Sandbox";

        if (Create(config))
        {
            Run();
        }
    }

    virtual ~Game()
    {

    }

    virtual void OnStart() override
    {
        m_WindowFlags |= ImGuiWindowFlags_MenuBar;

        m_Shaders = Simulacra::LoadShaders({ 
            { "VERTEX",     "assets/shaders/main.vert" },
            { "FRAGMENT",   "assets/shaders/main.frag" }
        });

        m_CurrentFileExplorerPath = std::filesystem::current_path();
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

        if (ImGui::Begin("File Explorer", nullptr, m_WindowFlags))
        {
            if (ImGui::Button("<-") && std::filesystem::canonical(m_CurrentFileExplorerPath) != std::filesystem::current_path())
            {
                m_CurrentFileExplorerPath /= "..";
            }

            ImGui::BeginChild("file_explorer_tab", ImVec2(0, ImGui::GetFrameHeightWithSpacing() * 7 + 30), true, ImGuiWindowFlags_HorizontalScrollbar);
            ImVec2 buttonSize(40, 40);
            for (auto const& dirEntry : Simulacra::ListFilesInDirectory(m_CurrentFileExplorerPath))
            {
                ImGui::SameLine();

                if (ImGui::Button(dirEntry.path().filename().string().c_str(), buttonSize) && std::filesystem::is_directory(dirEntry.path()))
                {
                    m_CurrentFileExplorerPath = dirEntry.path();
                }
            }
            ImGui::EndChild();
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
    std::filesystem::path m_CurrentFileExplorerPath;

    ImGuiWindowFlags m_WindowFlags;

    bool m_Modified;

    Simulacra::Shader m_Shaders;
};

int main()
{
    Game game;

    return 0;
}