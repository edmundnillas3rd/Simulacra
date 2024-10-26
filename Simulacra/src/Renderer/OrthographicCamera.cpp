#include "OrthographicCamera.h"

namespace Simulacra
{
    OrthographicCamera CreateCamera2D(float left, float right, float bottom, float top)
    {
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

        return { glm::vec2(0.0f, 0.0f), view, proj };
    };

    void UpdateCamera2D(OrthographicCamera& camera, const glm::vec3& transform)
    {
        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, transform);

        camera.View = view;
    }

    glm::mat4 CalculateViewProj(const OrthographicCamera& camera)
    {
        return camera.Projection * camera.View; 
    }
}