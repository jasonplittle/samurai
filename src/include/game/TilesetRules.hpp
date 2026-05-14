#pragma once

#include <glm/glm.hpp>
#include <unordered_set>

#include "Sprite.hpp"

typedef glm::ivec2 TileId;

enum class TileType
{
    Air,
    Grass,
    Dirt,
    Stone,
    Platform,
    Count
};

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

struct TileRules
{
    std::unordered_set<TileId> Up;
    std::unordered_set<TileId> Down;
    std::unordered_set<TileId> Left;
    std::unordered_set<TileId> Right;
};

struct Tile
{
    TileId Id;
    TileType Type;
    TileRules Rules;
    std::shared_ptr<Sprite> Spirte;
};

struct TileSet
{
    std::unordered_set<Tile> set;
};