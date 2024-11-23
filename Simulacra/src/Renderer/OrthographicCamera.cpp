#include "OrthographicCamera.h"

namespace Simulacra
{
    OrthographicCamera CreateCamera2D(float left, float right, float bottom, float top)
    {
        glm::mat4 view = glm::mat4(1.0f);

        OrthographicCamera camera;

        camera.Frustum = { left,  right, bottom, top };
        glm::mat4 proj = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);

        camera.Position = glm::vec3(0.0f);
        camera.View = view;
        camera.Projection = proj;

        return camera;
    };

    void UpdateCamera2D(OrthographicCamera& camera, const glm::vec3& transform)
    {
        camera.Position = transform;

        glm::mat4 view = glm::mat4(1.0f);
        view = glm::translate(view, transform);

        camera.View = glm::inverse(view);
    }

    glm::mat4 CalculateViewProj(const OrthographicCamera& camera)
    {
        return camera.Projection * camera.View; 
    }
}