#include "TileMap.hpp"

#include <iostream>


TileMap::TileMap(int width, int height)
    :
    m_width(width),
    m_height(height),
    m_tiles(width * height)
{}


Tile* TileMap::getTile(int x, int y)
{
    if (x < 0 || x >= m_width ||
            y < 0 || y >= m_height)
    {
        return nullptr;
    }

    Tile* tile = &m_tiles[y * m_width + x]; 

    return tile;
}

const Tile* TileMap::getTile(int x, int y) const
{
    return const_cast<TileMap*>(this)->getTile(x, y);
}

bool TileMap::IsSolid(int x, int y) const
{
    const Tile* tile = getTile(x, y);

    if (!tile) return true;

    return tile->IsSolid;
}

void TileMap::AddTile(int x, int y)
{
    Tile* tile = getTile(x, y);

    if (!tile) return;

    tile->IsSolid = true;
    tile->Mask = calculateMask(x, y);

    std::cout << (int)tile->Mask << std::endl;

    updateNeighbours(x, y);
}

void TileMap::RemoveTile(int x, int y)
{
    Tile* tile = getTile(x, y);

    if (!tile) return;

    tile->IsSolid = false;
    tile->Mask = calculateMask(x, y);

    updateNeighbours(x, y);
}

Mask TileMap::MaskAt(int x, int y) const
{
    const Tile* tile = getTile(x, y);

    // if (!tile) return -1;

    return tile->Mask;
}

Mask TileMap::calculateMask(int x, int y) const
{
    uint8_t mask = 0;

    if (IsSolid(x - 1, y - 1)) mask |= NW;
    if (IsSolid(x,     y - 1)) mask |= N;
    if (IsSolid(x + 1, y - 1)) mask |= NE;

    if (IsSolid(x - 1, y))     mask |= W;
    if (IsSolid(x + 1, y))     mask |= E;

    if (IsSolid(x - 1, y + 1)) mask |= SW;
    if (IsSolid(x,     y + 1)) mask |= S;
    if (IsSolid(x + 1, y + 1)) mask |= SE;

    return mask;
}

void TileMap::updateMask(int x, int y)
{
    Tile* tile = getTile(x, y);

    if (!tile) return;

    tile->Mask = calculateMask(x, y);
}

void TileMap::updateNeighbours(int x, int y)
{
    updateMask(x - 1, y - 1); // NW
    updateMask(x,     y - 1); // N
    updateMask(x + 1, y - 1); // NE

    updateMask(x - 1, y    ); // W
    updateMask(x + 1, y    ); // E

    updateMask(x - 1, y + 1); // SW;
    updateMask(x,     y + 1); // S
    updateMask(x + 1, y + 1); // SE
}
