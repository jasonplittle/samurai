#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "Sprite.hpp"


typedef glm::ivec2 TileId;
typedef int MaskId;


enum NeighborBits
{
    NW = 1 << 0, // 1
    N  = 1 << 1, // 2
    NE = 1 << 2, // 4
    W  = 1 << 3, // 8
    E  = 1 << 4, // 16
    SW = 1 << 5, // 32
    S  = 1 << 6, // 64
    SE = 1 << 7  // 128
};

struct TileSet
{
    std::unordered_map<uint8_t, TileId> Set;
    std::unique_ptr<Sprite> Sprite;
};

uint8_t CalculateMask(const TileMap& map, int x, int y)
{
    uint8_t mask = 0;

    auto Same = [&](int nx, int ny)
    {
        return map.IsSolid(nx, ny);
    };

    if (Same(x - 1, y - 1)) mask |= NW;
    if (Same(x,     y - 1)) mask |= N;
    if (Same(x + 1, y - 1)) mask |= NE;

    if (Same(x - 1, y))     mask |= W;
    if (Same(x + 1, y))     mask |= E;

    if (Same(x - 1, y + 1)) mask |= SW;
    if (Same(x,     y + 1)) mask |= S;
    if (Same(x + 1, y + 1)) mask |= SE;

    return mask;
}