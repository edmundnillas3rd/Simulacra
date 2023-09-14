#pragma once

#include <glm/glm.hpp>

namespace Simulacra
{
    enum class Shape3D : int
    {
        CUBE = 0,
        SPHERE = 1,
    };

    struct GameObject
    {
        std::string UUID;
        std::string Name;

        glm::vec3 Position;
        glm::vec3 Scale;
        glm::vec3 Rotation;

        Shape3D Type;
    };

    struct Scene
    {
        std::vector<GameObject> GameObjects;
        GameObject* SelectedGameObject;
    };

    extern Scene MainScene;

    void AddGameObject(std::string type);
    void UpdateScene();
}
