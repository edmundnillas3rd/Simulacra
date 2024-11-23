#include "Terrain.h"

#include <Simulacra.h>

#include <random>
#include <functional>

std::vector<Terrain> GenerateTerrain(const std::string& token, uint32_t width, uint32_t height)
{
    std::vector<Terrain> t;
    std::random_device rd;
    std::uniform_real_distribution<> distrib(0.01f, 1.0f);
    std::mt19937 mt;

    if (!token.empty())
    {
        std::seed_seq seq(token.begin(), token.end());
        mt.seed(seq);
    }
    else
    {
        mt = std::mt19937(rd());
    }

    for (size_t y = 0; y < height; y++)
    {
        for (size_t x = 0; x < width; x++)
        {
            auto random = distrib(mt);

            Terrain terrain;
            terrain.Position = glm::vec2(x * 16.0f, y * 16.0f);
            terrain.Width = 16;
            terrain.Height = 16;

            if (random > 0.50f)
            {
                terrain.Type = TerrainType::FLOOR;
            }
            else
            {
                terrain.Type = TerrainType::WALL;
            }

            t.push_back(terrain);
        }
    }

    return t;
}
