#include "Camera.h"

glm::vec3 RandomInUnitDisk()
{
    glm::vec3 p;
    do
    {
        p = 2.0f * glm::vec3(Utils::GetRandom(), Utils::GetRandom(), 0.0f) - glm::vec3(1.0f, 1.0f, 0.0f);
    } while (glm::dot(p, p) >= 1.0f);
    return p;
}

Ray GetCameraRay(Camera camera, float s, float t)
{
    Ray ray;

    glm::vec3 rd = camera.LensRadius * RandomInUnitDisk();
    glm::vec3 offset = camera.u * rd.x + camera.v * rd.y;
    ray.Origin = camera.Origin + offset;
    ray.Direction = camera.LowerLeftCorner + s * camera.Horizontal + t * camera.Vertical - camera.Origin - offset;

    return ray;
}