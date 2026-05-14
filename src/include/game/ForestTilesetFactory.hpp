#pragma once

#include "Tileset.hpp"


class ForestTilesetFactory
{
public:
    static TileSet CreateTileset()
    {
        TileSet tileSet;

        tileSet.Sprite = std::make_unique<Sprite>("resources/world/Tileset_v2.png", glm::vec2(32, 32));

        MaskId maskId = 3;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 6},
            .MaskId = maskId
        };

        return tileSet;
    }
};