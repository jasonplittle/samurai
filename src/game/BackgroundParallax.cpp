#include "BackgroundParallax.hpp"

#include <iostream>


BackgroundParallax::BackgroundParallax(ParallaxLayers parallaxLayers)
    : 
    m_parallaxLayers(std::move(parallaxLayers))
{}


void BackgroundParallax::RenderLayers(const SpriteRenderer& spriteRenderer, OrthographicCamera camera)
{
    for (auto& layer : m_parallaxLayers.set)
    {
        float parallaxX = camera.Pos.x * layer.ParallaxFactor * k_parallaxGlobalScale;
        float offset = fmod(-parallaxX, layer.Width);

        float baseX = offset + (std::floor((camera.Pos.x - offset) / layer.Width) * layer.Width);

        for (int i = 0; i <= 1; i++)
        {
            float x = baseX + (i * layer.Width);

            spriteRenderer.Render(
                *layer.Sprite,
                glm::vec2(0, 0),
                false,
                camera,
                glm::vec2(x, 0),
                glm::vec2(layer.Width, layer.Height)
            );
        }
    }
}
