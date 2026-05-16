#pragma once

#include <glm/glm.hpp>

#include "TileSet.hpp"
#include "TileMap.hpp"

#include "SpriteRenderer.hpp"
#include "Character.hpp"

constexpr int WORLD_WIDTH = 320;
constexpr int WORLD_HEIGHT = 180;
constexpr int TILE_SIZE = 32;

constexpr glm::ivec2 WORLD_GRID = { 10, 6 };


class World
{
public:
    World(TileSet tileSet);

    void ShowTile(bool show, int worldX, int worldY);
    void DrawTiles(SpriteRenderer& renderer, OrthographicCamera camera);

private:
    TileSet m_tileSet;
    TileMap m_tileMap;
};
