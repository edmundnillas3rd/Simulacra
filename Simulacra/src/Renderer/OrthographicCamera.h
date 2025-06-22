#pragma once

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Core/Window.h"

namespace Simulacra
{
    struct OrthographicCamera
    {
        glm::vec3 Position;
        glm::mat4 View;
        glm::mat4 Projection;

        struct Frustum
        {
            float Left;
            float Right;
            float Bottom;
            float Top;
        } Frustum;
    };

    OrthographicCamera CreateCamera2D(float left, float right, float bottom, float top);
    void UpdateCamera2D(OrthographicCamera& camera, const glm::vec3& transform);
    glm::mat4 CalculateViewProj(const OrthographicCamera& camera);
}

