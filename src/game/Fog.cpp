#include "Fog.hpp"


void Fog::Update(float dt)
{
    float wind = std::sin(dt * 0.2f);

    m_movement.x += 6 * wind * dt;
    m_movement.y = 0.5f * std::sin(dt * 0.1f);
}

void Fog::DrawFog(NoiseRenderer& renderer, OrthographicCamera& camera) const
{
    renderer.Render(
        *m_fogSprite,
        camera,
        camera.Pos,
        camera.Size,
        glm::vec2(1.f, 1.f),
        (camera.Pos / camera.Size) + m_movement,
        glm::vec4(0.45f, 0.50f, 0.60f, 0.32f)
    );
}