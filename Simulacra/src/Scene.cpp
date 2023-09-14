#include "Scene.h"

namespace Simulacra
{
    Scene MainScene;

    void AddGameObject(std::string type)
    {
        static int count;
        if (type == "Cube")
        {
            count++;
            GameObject go = { 
                "xxxxxx" + std::to_string(count),
                "GameObject" + std::to_string(count),
                glm::vec3(0.0f, 0.0f, -5.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                glm::vec3(1.0f, 1.0f, 1.0f),
                Shape3D::CUBE
            };
            MainScene.GameObjects.emplace_back(go);
        }
    }
    void UpdateScene()
    {
        for (auto it = MainScene.GameObjects.begin(); it != MainScene.GameObjects.end(); ++it)
        {
            GameObject& go = *it;
            if (go.UUID == MainScene.SelectedGameObject->UUID)
            {
                *it = *MainScene.SelectedGameObject;
            }
        }
    }
}
