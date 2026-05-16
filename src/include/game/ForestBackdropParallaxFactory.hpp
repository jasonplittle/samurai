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
                .ParallaxFactor = 0.1f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/3.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.3f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/2.png", glm::vec2(320, 180))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.6f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/1.png", glm::vec2(320, 180))
            }
        );

        return parallaxLayers;
    }
};