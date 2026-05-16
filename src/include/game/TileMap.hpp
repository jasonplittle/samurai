#pragma once

#include "TileSet.hpp"


struct Tile
{
    uint8_t Mask = 0;
    bool IsSolid = false;
};

class TileMap
{
public:
    TileMap(int width, int height);

    Tile* GetTile(int x, int y);
    const Tile* GetTile(int x, int y) const { return GetTile(x, y); };
    bool IsSolid(int x, int y) const;
    void AddTile(int x, int y);
    void RemoveTile(int x, int y);

private:
    uint8_t calculateMask(int x, int y) const;
    void updateMask(int x, int y);
    void updateNeighbours(int x, int y);


    std::vector<Tile> m_tiles;
    int m_width;
    int m_height;
};
