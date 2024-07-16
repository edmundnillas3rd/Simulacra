#include "Camera.h"

#include "Input.h"

namespace Simulacra
{
    glm::mat4 GetViewMatrix(Camera& camera)
    {
        return glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);
    }

    void UpdateCamera(Camera& camera, float velocity)
    {
        if (IsKeyPressed(SCANCODE::SCANCODE_W))
        {
            camera.Position += camera.Front * velocity;
        }

        if (IsKeyPressed(SCANCODE::SCANCODE_S))
        {
            camera.Position -= camera.Front * velocity;
        }

        if (IsKeyPressed(SCANCODE::SCANCODE_A))
        {
            camera.Position -= camera.Right * velocity;
        }

        if (IsKeyPressed(SCANCODE::SCANCODE_D))
        {
            camera.Position += camera.Right * velocity;
        }

    }
}