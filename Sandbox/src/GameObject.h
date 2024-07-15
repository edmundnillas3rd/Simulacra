#pragma once

#include <glm/glm.hpp>

class GameObject
{
public:
    GameObject() = default;
    ~GameObject() = default;

    glm::vec3 Position;
};