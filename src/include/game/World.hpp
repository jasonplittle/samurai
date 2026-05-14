#pragma once

#include <glm/glm.hpp>

#include "TileSet.hpp"

#include "SpriteRenderer.hpp"
#include "Character.hpp"

constexpr int WORLD_WIDTH = 320;
constexpr int WORLD_HEIGHT = 180;
constexpr int TILE_SIZE = 32;

constexpr glm::ivec2 WORLD_GRID = { 10, 5 };

struct Tile
{
    int NeighbourMask = 0;
    bool IsVisible = false;
};

class World
{
public:
    World(TileSet tileSet) : m_tileSet(std::move(tileSet)) {};

    Tile& GetTileByWorldGrid(int x, int y);
    Tile& GetTileByWorldPos(int x, int y);

    void ShowTile(bool show, int worldX, int worldY);

    void DrawTiles(SpriteRenderer& renderer, OrthographicCamera camera);


private:
    TileSet m_tileSet;
    Tile m_worldGrid[WORLD_GRID.x][WORLD_GRID.y];
};
