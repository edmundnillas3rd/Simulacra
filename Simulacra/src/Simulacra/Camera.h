#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "src/Events/Event.h"

namespace Simulacra
{
    struct Camera
    {
        static inline float YAW         = -90.0f;
        static inline float PITCH       =  0.0f;
        static inline float SPEED       =  2.5f;
        static inline float SENSITIVITY =  0.1f;
        static inline float ZOOM        =  45.0f;

        Camera() = default;
        Camera(uint32_t width, uint32_t height, glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
        {
            Width = width;
            Height = height;
            Position = position;
            WorldUp = up;
            Yaw = yaw;
            Pitch = pitch;
        }

        uint32_t Width;
        uint32_t Height;

        glm::vec3 Position;
        glm::vec3 Front;
        glm::vec3 Up;
        glm::vec3 Right;
        glm::vec3 WorldUp;

        float Yaw;
        float Pitch;

        float MovementSpeed;
        float MouseSensitivity;
        float Zoom;
    };

    glm::mat4 GetViewMatrix(Camera& camera);
    void UpdateCamera(Camera& camera, float velocity);
    void OnEventCamera(Camera& camera, Event& event);

    struct OrthographicCamera
    {
        OrthographicCamera() = default;
        OrthographicCamera(float left, float right, float bottom, float top)
            : ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f))
        {}

        glm::mat4 ProjectionMatrix;
        glm::mat4 ViewMatrix;
    };

    void SetOrthoCameraPosition(OrthographicCamera& camera, const glm::vec3 &position);
    glm::mat4 CalculateViewProjectionMatrix(const OrthographicCamera& camera);
}