#include "Ray.h"

glm::vec3 RayPointAtParameter(const Ray& ray, float t)
{
    return ray.Origin + t * ray.Direction;
}