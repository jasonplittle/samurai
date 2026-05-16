#pragma once

#include "BackgroundParallax.hpp"


class FeudalJapanBackdropParallaxFactory
{
public:
    static ParallaxLayers CreateBackdrop()
    {
        ParallaxLayers parallaxLayers;

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.1f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/1 (5).png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.3f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/1 (4).png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.6f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/1 (3).png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.9f,
                .Width = 320,
                .Height = 180,
                .Sprite = std::make_unique<Sprite>("resources/background/1 (2).png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        return parallaxLayers;
    }
};