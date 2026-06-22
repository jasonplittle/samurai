#pragma once

#include "BackgroundParallax.hpp"


class ForestBackdropParallaxFactory
{
public:
    static ParallaxLayers CreateBackdrop(float width, float height)
    {
        ParallaxLayers parallaxLayers;

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.25f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/forest/3.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.5f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/forest/2.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.8f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/forest/1.png", glm::vec2(320, 180))
            }
        );

        return parallaxLayers;
    }
};