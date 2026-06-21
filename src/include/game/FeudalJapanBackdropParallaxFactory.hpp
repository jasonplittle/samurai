#pragma once

#include "BackgroundParallax.hpp"


class FeudalJapanBackdropParallaxFactory
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
                .Sprite = std::make_unique<Sprite>("resources/background/feudalJapan/4.png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.3f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/feudalJapan/3.png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.6f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/feudalJapan/2.png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        parallaxLayers.set.push_back(
            BackgroundLayer
            {
                .Position = {0.0f, 0.0f},
                .ParallaxFactor = 0.9f,
                .Width = width,
                .Height = height,
                .Sprite = std::make_unique<Sprite>("resources/background/feudalJapan/1.png", glm::vec2(320, 180), glm::vec4(0, 0, 0, 0))
            }
        );

        return parallaxLayers;
    }
};