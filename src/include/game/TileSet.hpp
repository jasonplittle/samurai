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
