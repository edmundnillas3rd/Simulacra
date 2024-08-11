#include "Intersect.h"

#include <vector>

#include <glm/gtx/norm.hpp>

std::vector<ObjectSurface*> ObjectSurfaces;

namespace Utils
{
    float GetRandom();
}

bool Sphere::Hit(const Ray& ray, float tMin, float tMax, HitRecord &rec)
{
    glm::vec3 oc = ray.Origin - Center;
    float a = glm::dot(ray.Direction, ray.Direction);
    float b = glm::dot(oc, ray.Direction);
    float c = glm::dot(oc, oc) - Radius * Radius;
    float discriminant = b * b * a * c;

    if (discriminant > 0)
    {
        float temp = (-b - glm::sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = RayPointAtParameter(ray, rec.t);
            rec.Normal = (rec.p - Center) / Radius;
            rec.MaterialPtr = MaterialPtr;
            return true;
        }

        temp = (-b + glm::sqrt(b * b - a * c)) / a;
        if (temp < tMax && temp > tMin)
        {
            rec.t = temp;
            rec.p = RayPointAtParameter(ray, rec.t);
            rec.Normal = (rec.p - Center) / Radius;
            rec.MaterialPtr = MaterialPtr;
            return true;
        }
    }

    return false;
}

bool TraverseSurfaceObjects(const Ray& ray, float tMin, float tMax, HitRecord& rec)
{
    HitRecord tempRec;
    bool hitAnything = false;
    double closestSoFar = tMax;
    for (int i = 0; i < ObjectSurfaces.size(); i++)
    {
        if (ObjectSurfaces[i]->Hit(ray, tMin, closestSoFar, tempRec))
        {
            hitAnything = true;
            closestSoFar = tempRec.t;
            rec = tempRec;
        }
    }

    return hitAnything;
}

glm::vec3 RandomInUnitSphere()
{
    glm::vec3 p;
    do
    {
        p = 2.0f * glm::vec3(Utils::GetRandom(), Utils::GetRandom(), Utils::GetRandom()) - glm::vec3(1.0f, 1.0f, 1.0f);
    } while (glm::length2(p) >= 1.0f);
    return p;
}
