#include <Simulacra.h>

#include <SDL2/SDL.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Terrain/Terrain.h"

class Sandbox : public Simulacra::ApplicationLayer
{
public:
    Sandbox()
    {
    }

    ~Sandbox()
    {

    }

    void OnStart()
    {
        m_Texture = Simulacra::LoadTexture("Sandbox/assets/2D Pixel Dungeon Asset Pack/character and tileset/Dungeon_Character.png");
        m_Camera = Simulacra::CreateCamera2D(0.0f, 1280.0f, 640.0f, 0.0f);
        m_Terrain = GenerateTerrain("HelloWorl", 100, 500);
    }

    void OnEvent(Simulacra::Event event)
    {
    }

    void OnUpdate(float deltaTime)
    {
        Simulacra::BeginScene(m_Camera);

        // glm::mat4 transform = glm::mat4(1.0f);
        // transform = glm::translate(transform, glm::vec3(190.0f, 160.0f, 0.0f));
        // Simulacra::DrawSprite(m_Texture, transform);

        // TODO(Edmund): Add the input modules
        const Uint8* state = SDL_GetKeyboardState(nullptr);

        if (state[SDL_SCANCODE_A])
            m_Camera.Position.x -= 10.0f;
        else if (state[SDL_SCANCODE_D])
            m_Camera.Position.x += 10.0f;
        else if (state[SDL_SCANCODE_W])
            m_Camera.Position.y -= 10.0f;
        else if (state[SDL_SCANCODE_S])
            m_Camera.Position.y += 10.0f;

        
        Simulacra::UpdateCamera2D(m_Camera, m_Camera.Position);

        std::vector<Terrain> terrains;

        std::copy_if(m_Terrain.begin(), m_Terrain.end(), std::back_inserter(terrains), [this](Terrain terrain) {
            return (terrain.Position.x - m_Camera.Position.x >= m_Camera.Frustum.Left
                && terrain.Position.x + terrain.Width - m_Camera.Position.x <= m_Camera.Frustum.Right
                && terrain.Position.y - m_Camera.Position.y >= m_Camera.Frustum.Top
                && terrain.Position.y + terrain.Height - m_Camera.Position.y <= m_Camera.Frustum.Bottom
            );
        });

        for (const auto& terrain : terrains)
        {
            glm::mat4 transform = glm::mat4(1.0f);
            transform = glm::translate(transform, glm::vec3(terrain.Position.x, terrain.Position.y, 0.0f));

            if (terrain.Type == TerrainType::FLOOR)
            {
                Simulacra::DrawSprite(m_Texture, transform, 16.0f, 16.0f, 0, 16.0f);
            }
            else
            {
                Simulacra::DrawSprite(m_Texture, transform, 16.0f, 16.0f, 16.0f, 16.0f);
            }
        }

        Simulacra::ConsoleLog("Number of drawn objects inside the frustum: {}", terrains.size());

        Simulacra::EndScene();
    }

private:
    Simulacra::Texture m_Texture;
    Simulacra::OrthographicCamera m_Camera;
    std::vector<Terrain> m_Terrain;
};

int main(int argc, char* argv[])
{
    Simulacra::CreateApplication("Simulacra", 1280, 720);
    Simulacra::PushApplicationLayer(new Sandbox());
    Simulacra::RunApplication();
    return 0;
}