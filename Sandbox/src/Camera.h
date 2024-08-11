#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

#include "Ray.h"

namespace Utils
{
    float GetRandom();
}

glm::vec3 RandomInUnitDisk();

struct Camera
{
    Camera()
    : Origin(glm::vec3(0.0f, 0.0f, 0.0f)), LowerLeftCorner(glm::vec3(-2.0f, -1.0f, -1.0f)), Horizontal(glm::vec3(4.0f, 0.0f, 0.0f)), Vertical(glm::vec3(0.0f, 2.0f, 0.0f))
    {}

    Camera(glm::vec3 o, glm::vec3 c, glm::vec3 right, glm::vec3 up)
    : Origin(o), LowerLeftCorner(c), Horizontal(right), Vertical(up)
    {}

    Camera(glm::vec3 lookFrom, glm::vec3 lookAt, glm::vec3 up, float fov, float aspect, float aperture, float focusDist)
    {
        LensRadius = aperture / 2.0f;
        float theta = fov * glm::pi<float>() / 180;
        float halfHeight = glm::tan(theta / 2);
        float halfWidth = aspect * halfHeight;
        Origin = lookFrom;
        w = glm::normalize(lookFrom - lookAt);
        u = glm::normalize(glm::cross(up, w));
        v = glm::cross(w, u);
        LowerLeftCorner = Origin - halfWidth * focusDist * u - halfHeight * focusDist * v - focusDist * w;
        Horizontal = 2.0f * halfWidth * focusDist * u;
        Vertical = 2.0f * halfHeight * focusDist * v;
    }

    glm::vec3 u, v, w;
    glm::vec3 Origin;
    glm::vec3 LowerLeftCorner;
    glm::vec3 Horizontal;
    glm::vec3 Vertical;
    float LensRadius;
};

Ray GetCameraRay(Camera camera, float u, float v);