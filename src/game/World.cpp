#include "World.hpp"

#include <iostream>

#define BIT(i) 1 << i

World::World(TileSet tileSet) : m_tileSet(std::move(tileSet))
{
    for (int x = 0; x < WORLD_GRID.x; x++)
    {
        for (int y = 0; y < WORLD_GRID.y; y++)
        {
            m_worldGrid[x][y] = Tile { .NeighbourMask = 0, .IsVisible = false };
        }
    }
};


Tile* World::GetTileByWorldGrid(int x, int y)
{
    if (x >= 0 && x < WORLD_GRID.x && y >= 0 && y < WORLD_GRID.y)
    {
        return &m_worldGrid[x][y];    
    }

    std::cout << "World grid null: " << x << ", " << y << std::endl;

    return nullptr;
}

Tile* World::GetTileByWorldPos(int x, int y)
{
    int gridX = std::floor(x / TILE_SIZE);
    int gridY = std::floor(y / TILE_SIZE);

    return GetTileByWorldGrid(gridX, gridY);
}

void World::ShowTile(bool show, int worldX, int worldY)
{
    Tile* tile = GetTileByWorldPos(worldX, worldY);

    if (!tile) return;
    if (tile->IsVisible == show) return;

    tile->IsVisible = show;
    tile->NeighbourMask = 0;

                           //   N        W      E      S       NW      NE       SW      SE
    int neighbourOffset[16] = { 0, -1,  -1, 0,  1, 0,  0, 1,  -1, -1,  1, -1,  -1, 1,  -1, -1 };


    for (int x = 0; x < WORLD_GRID.x; x++)
    {
        for (int y = 0; y < WORLD_GRID.y; y++)
        {
            Tile* gridTtile = GetTileByWorldGrid(x, y);
            gridTtile->NeighbourMask = 0;

            if (!gridTtile->IsVisible) 
            {
                continue;
            }

            int cout = 0;

            for (int n = 0; n < 4; n++)
            {
                Tile* neighbour = GetTileByWorldGrid(x + neighbourOffset[n * 2], y + neighbourOffset[(n * 2) + 1]);

                if (!neighbour || neighbour->IsVisible)
                {
                    gridTtile->NeighbourMask |= BIT(n);
                }
            }

            if (tile == gridTtile){
                std::cout << "Neighbour count: " << cout << " - mask: " << tile->NeighbourMask << std::endl;
            }
            
        }
    }
}

void World::DrawTiles(SpriteRenderer& spriteRenderer, OrthographicCamera camera)
{
    for (int x = 0; x < WORLD_GRID.x; x++)
    {
        for (int y = 0; y < WORLD_GRID.y; y++)
        {
            Tile* tile = GetTileByWorldGrid(x, y);

            if (!tile->IsVisible) 
            {
                continue;
            }

            spriteRenderer.Render(
                *m_tileSet.Sprite,
                m_tileSet.Set[tile->NeighbourMask].TileId,
                false,
                camera,
                glm::vec2((x * TILE_SIZE) - (0.5 * camera.Size.x) + (TILE_SIZE * 0.5), 
                    (camera.Size.y * 0.5) - (y * TILE_SIZE) - (TILE_SIZE * 0.5)),
                glm::vec2(TILE_SIZE, TILE_SIZE)
            );
        }
    }
}