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

        float x = fmod(-parallaxX, screenSize.x);

        // std::cout << x << std::endl;
        // std::cout << cameraPos.x << ", " << cameraPos.y << std::endl;

        // std::cout << renderPos.x << ", " << renderPos.y
        spriteRenderer.Render(
            *layer.Sprite,
            glm::vec2(0, 0),
            false,
            cameraPos,
            screenSize,
            glm::vec2(x, 0),
            glm::vec2(layer.Width, layer.Height)
        );
  
        spriteRenderer.Render(
            *layer.Sprite,
            glm::vec2(0, 0),
            false,
            cameraPos,
            screenSize,
            glm::vec2(x + layer.Width, 0),
            glm::vec2(layer.Width, layer.Height)
        );
    }
}