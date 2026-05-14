#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

#include "Sprite.hpp"


typedef glm::ivec2 TileId;
typedef int MaskId;


struct TileType
{
    TileId TileId;
    MaskId MaskId;
};

struct TileSet
{
    std::unordered_map<MaskId, TileType> Set;
    std::unique_ptr<Sprite> Sprite;
};