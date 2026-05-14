#include "BackgroundParallax.hpp"

#include <iostream>


BackgroundParallax::BackgroundParallax(ParallaxLayers parallaxLayers)
    : 
    m_parallaxLayers(std::move(parallaxLayers))
{}


void BackgroundParallax::RenderLayers(const SpriteRenderer& spriteRenderer, glm::vec2 cameraPos, glm::vec2 screenSize)
{
    for (auto& layer : m_parallaxLayers.set)
    {
        float parallaxX = cameraPos.x * layer.ParallaxFactor * k_parallaxGlobalScale;
        float offset = fmod(-parallaxX, layer.Width);

        float baseX = offset + (std::floor((cameraPos.x - offset) / layer.Width) * layer.Width);

        for (int i = 0; i <= 1; i++)
        {
            float x = baseX + (i * layer.Width);

            spriteRenderer.Render(
                *layer.Sprite,
                glm::vec2(0, 0),
                false,
                cameraPos,
                screenSize,
                glm::vec2(x, 0),
                glm::vec2(layer.Width, layer.Height)
            );
        }
    }
}
