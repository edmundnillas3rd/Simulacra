#include "Material.h"

namespace Utils
{
    float GetRandom();
}

bool Lambertian::Scatter(const Ray &rIn, const HitRecord &rec, glm::vec3& attenuation, Ray &scattered) const
{
    glm::vec3 target = rec.p + rec.Normal + RandomInUnitSphere();

    Ray ray;
    ray.Origin = rec.p;
    ray.Direction = target - rec.p;

    scattered = ray;
    attenuation = Albedo;

    return true;
}

bool Metal::Scatter(const Ray &rIn, const HitRecord &rec, glm::vec3& attenuation, Ray &scattered) const
{
    glm::vec3 reflected = Reflect(glm::normalize(rIn.Direction), rec.Normal);
    Ray ray;
    ray.Origin = rec.p;
    ray.Direction = reflected + Fuzz * RandomInUnitSphere();
    scattered = ray;
    attenuation = Albedo;

    return (glm::dot(scattered.Direction, rec.Normal) > 0);
}

bool Dielectric::Scatter(const Ray &rIn, const HitRecord &rec, glm::vec3 &attenuation, Ray &scattered) const
{
    glm::vec3 outwardNormal;
    glm::vec3 reflected = Reflect(rIn.Direction, rec.Normal);
    float niOvernt;
    attenuation = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::vec3 refracted;
    float reflectProb;
    float cosine;

    if (glm::dot(rIn.Direction, rec.Normal) > 0)
    {
        outwardNormal = -rec.Normal;
        niOvernt = RefIdx;
        cosine = RefIdx * glm::dot(rIn.Direction, rec.Normal) / glm::length(rIn.Direction);
    }
    else
    {
        outwardNormal = rec.Normal;
        niOvernt = 1.0f / RefIdx;
        cosine = -glm::dot(rIn.Direction, rec.Normal) / glm::length(rIn.Direction);
    }

    if (Refract(rIn.Direction, outwardNormal, niOvernt, refracted))
    {
        reflectProb = Schlick(cosine, RefIdx);
    }
    else
    {
        Ray ray;
        ray.Origin = rec.p;
        ray.Direction = reflected;
        scattered = ray;
        reflectProb = 1.0f;
    }

    if (Utils::GetRandom() < reflectProb)
    {
        Ray ray;
        ray.Origin = rec.p;
        ray.Direction = reflected;
        scattered = ray;
    }
    else
    {
        Ray ray;
        ray.Origin = rec.p;
        ray.Direction = refracted;
        scattered = ray;
    }

    return true;
}

glm::vec3 Reflect(const glm::vec3 &v, const glm::vec3 &n)
{
    return v - 2.0f * glm::dot(v, n) * n;
}

bool Refract(const glm::vec3& v, const glm::vec3& n, float niOvernt, glm::vec3& refracted)
{
    glm::vec3 uv = glm::normalize(v);
    float dt = glm::dot(uv, n);
    float discriminant = 1.0f - niOvernt * niOvernt * (1.0f - dt * dt);
    if (discriminant > 0)
    {
        refracted = niOvernt * (uv - n * dt) - n * glm::sqrt(discriminant);
        return true;
    }
    else
        return false;
}

float Schlick(float cosine, float refIdx)
{
    float r0 = (1 - refIdx) / (1 + refIdx);
    r0 = r0 * r0;
    return r0 + (1.0f - r0) * glm::pow((1.0f - cosine), 5);
}