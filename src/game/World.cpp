#include "World.hpp"

#include <iostream>

#define BIT(i) 1 << i

World::World(TileSet tileSet) : m_tileSet(std::move(tileSet)), m_tileMap(WORLD_WIDTH, WORLD_HEIGHT) {};


static glm::ivec2 worldToGrid(int x, int y)
{
    int gridX = std::floor(x / TILE_SIZE);
    int gridY = std::floor(y / TILE_SIZE);

    return glm::ivec2(gridX, gridY);
}

void World::ShowTile(bool show, int worldX, int worldY)
{
    glm::ivec2 pos = worldToGrid(worldX, worldY);
    
    if (show == m_tileMap.IsSolid(pos.x, pos.y)) 
        return;

    if (show)
    {
        m_tileMap.AddTile(pos.x, pos.y);
    }
    else
    {
        m_tileMap.RemoveTile(pos.x, pos.y);
    }
}


void World::DrawTiles(SpriteRenderer& spriteRenderer, OrthographicCamera camera)
{
    for (int x = 0; x < WORLD_GRID.x; x++)
    {
        for (int y = 0; y < WORLD_GRID.y; y++)
        {
            if (!m_tileMap.IsSolid(x, y)) 
                continue;


            spriteRenderer.Render(
                *m_tileSet.Sprite,
                m_tileSet.Set[m_tileMap.MaskAt(x, y)],
                false,
                camera,
                glm::vec2((x * TILE_SIZE) - (0.5 * camera.Size.x) + (TILE_SIZE * 0.5), 
                    (camera.Size.y * 0.5) - (y * TILE_SIZE) - (TILE_SIZE * 0.5)),
                glm::vec2(TILE_SIZE, TILE_SIZE)
            );
        }
    }
}