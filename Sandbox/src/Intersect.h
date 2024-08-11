#pragma once

#include "Ray.h"

#include <glm/glm.hpp>

struct Material;

struct HitRecord
{
    float t;
    glm::vec3 p;
    glm::vec3 Normal;
    Material* MaterialPtr;
};

struct ObjectSurface
{
    virtual bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec) = 0;
};

struct Sphere : ObjectSurface
{
    Sphere() = default;
    Sphere(glm::vec3 c, float r)
        : Center(c), Radius(r)
    {}
    Sphere(glm::vec3 c, float r, Material* m)
        :  Center(c), Radius(r), MaterialPtr(m)
    {}
    virtual ~Sphere() = default;
    
    bool Hit(const Ray& ray, float tMin, float tMax, HitRecord& rec);

    glm::vec3 Center;
    float Radius;
    Material* MaterialPtr;
};

extern std::vector<ObjectSurface*> ObjectSurfaces;

bool TraverseSurfaceObjects(const Ray& ray, float tMin, float tMax, HitRecord& rec);

glm::vec3 RandomInUnitSphere();