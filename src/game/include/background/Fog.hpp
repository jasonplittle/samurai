#pragma once

#include "Sprite.hpp"
#include "NoiseRenderer.hpp"


class Fog
{
public:
    void Update(float dt);
    void DrawFog(NoiseRenderer& renderer, OrthographicCamera& camera, glm::vec2 offset, float depth) const;



private:
    float m_time = 0;
    glm::vec2 m_fogOffset = glm::vec2(0, 0);
    std::unique_ptr<Sprite> m_fogSprite = std::make_unique<Sprite>("resources/atmosphere/fog.jpg", glm::vec2(1000, 1000));

};
