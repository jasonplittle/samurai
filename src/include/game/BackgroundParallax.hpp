#pragma once

#include <glm/glm.hpp>

#include "Sprite.hpp"
#include "SpriteRenderer.hpp"

struct BackgroundLayer
{
    glm::vec2 Position;

    float ParallaxFactor;

    float Width;
    float Height;

    std::unique_ptr<Sprite> Sprite;
};

struct ParallaxLayers
{
    std::vector<BackgroundLayer> set;
};


class BackgroundParallax
{
public:
    BackgroundParallax(ParallaxLayers parallaxLayers);
    void RenderLayers(const SpriteRenderer& spriteRenderer, OrthographicCamera camera);

private:
    ParallaxLayers m_parallaxLayers;

    const float k_parallaxGlobalScale = 0.5f;

};
