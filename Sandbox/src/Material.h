#pragma once

#include "Ray.h"
#include "Intersect.h"

struct Material
{
    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const = 0;
};

struct Lambertian : Material
{
    Lambertian(const glm::vec3& a)
        : Albedo(a)
    {}

    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const;
    glm::vec3 Albedo;

};

struct Metal : Material
{
    Metal(const glm::vec3& a, float f)
        : Albedo(a) 
    {
        if (f < 1)
            Fuzz = f;
        else
            Fuzz = 1;
    }

    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const;

    glm::vec3 Albedo;
    float Fuzz;
};

struct Dielectric : Material
{
    Dielectric(float ri)
        : RefIdx(ri)
    {}

    virtual bool Scatter(const Ray& rIn, const HitRecord& rec, glm::vec3& attenuation, Ray& scattered) const;
    float RefIdx;
};

glm::vec3 Reflect(const glm::vec3& v, const glm::vec3& n);
bool Refract(const glm::vec3& v, const glm::vec3& n, float niOvernt, glm::vec3& refracted);
float Schlick(float cosine, float refIdx);