#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace Simulacra
{
    struct OrthographicCamera
    {
        glm::vec2 Position;
        glm::mat4 View;
        glm::mat4 Projection;
    };

    OrthographicCamera CreateCamera2D(float left, float right, float bottom, float top);
    void UpdateCamera2D(OrthographicCamera& camera, const glm::vec3& transform);
    glm::mat4 CalculateViewProj(const OrthographicCamera& camera);
}

