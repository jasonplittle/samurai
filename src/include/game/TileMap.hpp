#pragma once

#include "TileSet.hpp"


struct Tile
{
    Mask Mask = 0;
    bool IsSolid = false;
};

class TileMap
{
public:
    TileMap(int width, int height);
    
    bool IsSolid(int x, int y) const;
    void AddTile(int x, int y);
    void RemoveTile(int x, int y);

    Mask MaskAt(int x, int y) const;

private:
    Mask calculateMask(int x, int y) const;
    void updateMask(int x, int y);
    void updateNeighbours(int x, int y);

    Tile* getTile(int x, int y);
    const Tile* getTile(int x, int y) const;

private:
    std::vector<Tile> m_tiles;
    int m_width;
    int m_height;
};
