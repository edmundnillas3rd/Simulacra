#include "Camera.h"

#include "src/Events/MouseEvents.h"

#include "Input.h"
#include "Window.h"

namespace Simulacra
{
    bool n_FirstMouse = true;
    float lastX = (float)1280 / 2.0f;
    float lastY = (float)680 / 2.0f;

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

    void OnEventCamera(Camera& camera, Event& event)
    {
        if (event.Type() == Simulacra::EventType::MOUSE_MOVED)
        {
            const auto key = dynamic_cast<MouseMovedEvent*>(&event);
            float xpos = (float)key->X;
            float ypos = (float)key->Y;
            

            if (n_FirstMouse)
            {
                lastX = xpos;
                lastX = ypos;
                n_FirstMouse = false;
            }

            float xoffset = xpos - lastX;
            float yoffset = lastY - ypos;

            lastX = xpos;
            lastY = ypos;

            xoffset *= camera.MouseSensitivity;
            yoffset *= camera.MouseSensitivity;

            camera.Yaw   += xoffset;
            camera.Pitch += yoffset;

            bool constrainPitch = true;
            if (constrainPitch)
            {
                if (camera.Pitch > 89.0f)
                    camera.Pitch = 89.0f;
                if (camera.Pitch < -89.0f)
                    camera.Pitch = -89.0f;
            } 
        }

        glm::vec3 front;

        front.x = cos(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
        front.y = sin(glm::radians(camera.Pitch));
        front.z = sin(glm::radians(camera.Yaw)) * cos(glm::radians(camera.Pitch));
        camera.Front = glm::normalize(front);
        camera.Right = glm::normalize(glm::cross(camera.Front, camera.WorldUp));
        camera.Up = glm::normalize(glm::cross(camera.Right, camera.Front));
    }
}