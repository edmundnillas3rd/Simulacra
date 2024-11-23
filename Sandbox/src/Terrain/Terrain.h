#pragma once
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <Simulacra.h>

enum class TerrainType : uint32_t
{
    WALL,
    FLOOR,
};

struct Terrain
{
    TerrainType Type;
    glm::vec2 Position;
    uint32_t Width, Height;
};


std::vector<Terrain> GenerateTerrain(const std::string& token, uint32_t width, uint32_t height);