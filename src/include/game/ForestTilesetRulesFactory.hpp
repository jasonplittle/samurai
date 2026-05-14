#pragma once

#include "TilesetRules.hpp"


class ForestTilesetRulesFactory
{
public:
    static TilesetRules CreateTilesetRules()
    {
        TileSet tileSet;



        tileSet.set.insert(
            Tile
            {
                .Id = TileId(0, 0),
                .Type = TileType::Air
                .Rules.Up
            }
        );



        std::shared_ptr<Sprite> tilesetSprite = std::make_shared<Sprite>("resources/world/tileset_v2.png", glm::vec2(32, 32));



        ParallaxLayers parallaxLayers;

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.1f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/3.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.3f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/2.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.6f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/1.png", glm::vec2(320, 180))
            }
        );

        return parallaxLayers;
    }
};