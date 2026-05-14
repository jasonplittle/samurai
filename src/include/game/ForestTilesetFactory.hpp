#pragma once

#include "Tileset.hpp"


class ForestTilesetFactory
{
public:
    static TileSet CreateTileset()
    {
        TileSet tileSet;

        tileSet.Sprite = std::make_unique<Sprite>("resources/world/Tileset_v2.png", glm::vec2(32, 32));

        MaskId maskId = 0;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 6},
            .MaskId = maskId
        };

        MaskId maskId = 1;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 7},
            .MaskId = maskId
        };

        MaskId maskId = 2;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {3, 6},
            .MaskId = maskId
        };

        MaskId maskId = 3;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {3, 7},
            .MaskId = maskId
        };

        MaskId maskId = 4;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {1, 6},
            .MaskId = maskId
        };

        MaskId maskId = 5;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {1, 7},
            .MaskId = maskId
        };

        MaskId maskId = 6;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {2, 6},
            .MaskId = maskId
        };

        MaskId maskId = 7;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 9},
            .MaskId = maskId
        };

        MaskId maskId = 8;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 9},
            .MaskId = maskId
        };

        MaskId maskId = 9;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {4, 8},
            .MaskId = maskId
        };

        MaskId maskId = 10;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {3, 9},
            .MaskId = maskId
        };

        MaskId maskId = 11;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {3, 8},
            .MaskId = maskId
        };

        MaskId maskId = 12;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {1, 9},
            .MaskId = maskId
        };

        MaskId maskId = 13;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {1, 8},
            .MaskId = maskId
        };

        MaskId maskId = 14;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {2, 9},
            .MaskId = maskId
        };

        MaskId maskId = 15;
        tileSet.Set[maskId] = 
        TileType {
            .TileId = {2, 8},
            .MaskId = maskId
        };

        return tileSet;
    }
};