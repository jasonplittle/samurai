#include "World.hpp"

#include <iostream>

Tile& World::GetTileByWorldGrid(int x, int y)
{
    if (x > 0 && x <= WORLD_GRID.x && y > 0 && y < WORLD_GRID.y)
    {
        
    }

    return m_worldGrid[x][y];
}


Tile& World::GetTileByWorldPos(int x, int y)
{
    int gridX = std::floor(x / TILE_SIZE);
    int gridY = std::floor(y / TILE_SIZE);

    return GetTileByWorldGrid(gridX, gridY);
}

void World::ShowTile(bool show, int worldX, int worldY)
{
    Tile& tile = GetTileByWorldPos(worldX, worldY);
    tile.IsVisible = show;
    tile.NeighbourMask = 0;
}

void World::DrawTiles(SpriteRenderer& spriteRenderer, OrthographicCamera camera)
{
    spriteRenderer.Render(
        *m_tileSet.Sprite,
        glm::vec2(1, 1),
        // m_tileSet.Set[0].TileId,
        false,
        camera,
        glm::vec2(0, 0),
        glm::vec2(TILE_SIZE, TILE_SIZE)
    );


    return;


    for (int x = 0; x < WORLD_GRID.x; x++)
    {
        for (int y = 0; y < WORLD_GRID.y; y++)
        {
            Tile& tile = GetTileByWorldGrid(x, y);

            if (tile.IsVisible)
            {
                spriteRenderer.Render(
                    *m_tileSet.Sprite,
                    m_tileSet.Set[0].TileId, 
                    false,
                    camera,
                    glm::vec2(x, y),
                    glm::vec2(TILE_SIZE, TILE_SIZE)
                );
            }
        }
    }
}