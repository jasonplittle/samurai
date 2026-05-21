#pragma once

#include <glm/glm.hpp>

#include "TileSet.hpp"
#include "TileMap.hpp"

#include "SpriteRenderer.hpp"


constexpr int WORLD_WIDTH = 640;
constexpr int WORLD_HEIGHT = 360;
constexpr int TILE_SIZE = 32;
constexpr int HALF_TILE_SIZE = 16;

constexpr glm::ivec2 WORLD_GRID = { 20, 12 };


class World
{
public:
    World(TileSet tileSet);

    bool IsSolid(int worldX, int worldY) const;
    void ShowTile(bool show, int worldX, int worldY);
    void DrawTiles(SpriteRenderer& renderer, OrthographicCamera camera);

    int WorldYToTileTopY(int worldY) const;
    int WorldYToTileBottomY(int worldY) const;
    int WorldXToTileRightX(int worldX) const;
    int WorldXToTileLeftX(int worldX) const;

    void CreateDefaultWorld();

private:
    TileSet m_tileSet;
    TileMap m_tileMap;
};
