#pragma once

#include "Tileset.hpp"


class ForestTilesetFactory
{
public:
    static TileSet CreateTileSet()
    {
        TileSet tileSet;
        tileSet.Sprite = std::make_unique<Sprite>("resources/world/Tileset.png", glm::vec2(32, 32));

        // In sprite-sheet order. Top-left to bottom-right.

        tileSet.Set[E | S | SE] = {1, 4};
        tileSet.Set[W | E | SW | S | SE] = {2, 4};
        tileSet.Set[W | SW | S ] = {3, 4};
        tileSet.Set[S] = {4, 4};
        tileSet.Set[E | S] = {5, 4};
        tileSet.Set[W | E | SW | S] = {6, 4};
        tileSet.Set[W | E | S | SE] = {7, 4};
        tileSet.Set[W | S] = {8, 4};
        tileSet.Set[W | E | S] = {9, 4};
        tileSet.Set[NW | N | W | E | S | SE] = {10, 4};

        tileSet.Set[N | NE | E | S | SE] = {1, 3};
        tileSet.Set[NW | N | NE | W | E | SW | S | SE] = {2, 3};
        tileSet.Set[NW | N | W | SW | S] = {3, 3};
        tileSet.Set[N | S] = {4, 3};
        tileSet.Set[N | NE | E | S] = {5, 3};
        tileSet.Set[NW | N | NE | W | E | SW | S] = {6, 3};
        tileSet.Set[NW | N | NE | W | E | S | SE] = {7, 3};
        tileSet.Set[NW | N | W | S] = {8, 3};
        tileSet.Set[NW | N | NE | W | E | S] = {9, 3};
        tileSet.Set[NW | N | W | E | S | SE] = {10, 3};

        tileSet.Set[N | NE | E] = {1, 2};
        tileSet.Set[NW | N | NE] = {2, 2};
        tileSet.Set[NW | N | W] = {3, 2};
        tileSet.Set[N] = {4, 2};
        tileSet.Set[N | E | S | SE] = {5, 2};
        tileSet.Set[NW | N | W | E | SW | S | SE] = {6, 2};
        tileSet.Set[N | NE | W | E | SW | S | SE] = {7, 2};
        tileSet.Set[N | W | SW | S] = {8, 2};
        tileSet.Set[N | W | E | SW | S | SE] = {9, 2};
        tileSet.Set[N | W | E | S | SE] = {10, 2};
        tileSet.Set[N | W | E | SW | S] = {11, 2};

        tileSet.Set[E] = {1, 1};
        tileSet.Set[W | E] = {2, 1};
        tileSet.Set[W] = {3, 1};
        tileSet.Set[0] = {4, 1};
        tileSet.Set[N | E] = {5, 1};
        tileSet.Set[NW | N | W | E] = {6, 1};
        tileSet.Set[N | NE | E | W] = {7, 1};
        tileSet.Set[N | W] = {8, 1};
        tileSet.Set[N | W | E] = {9, 1};
        tileSet.Set[N | NE | W | E | S] = {10, 1};
        tileSet.Set[NW | N | W | E | S] = {11, 1};

        tileSet.Set[N | E | S] = {5, 0};
        tileSet.Set[NW | N | W | E | SW | S] = {6, 0};
        tileSet.Set[N | NE | W | E | S | SE] = {7, 0};
        tileSet.Set[N | W | S] = {8, 0};
        tileSet.Set[N | W | E | S] = {9, 0};

        return tileSet;
    }
};