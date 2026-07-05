#include "Fog.hpp"


void Fog::Update(float dt)
{
    m_time += dt;

    float windX =
        0.009f
        + 0.004f * std::sin(m_time * 0.11f)
        + 0.002f * std::sin(m_time * 0.37f)
        + 0.001f * std::sin(m_time * 0.91f);

    float windY =
        0.004f * std::sin(m_time * 0.21f)
        + 0.006f * std::sin(m_time * 0.73f);

    m_fogOffset += glm::vec2(windX, windY) * dt;
}

void Fog::DrawFog(NoiseRenderer& renderer, OrthographicCamera& camera, glm::vec2 offset, float depth) const
{
    renderer.Render(
        *m_fogSprite,
        camera,
        camera.Pos,
        camera.Size,
        glm::vec2(1.f, 1.f),
        ((camera.Pos * depth) / camera.Size) + m_fogOffset + offset,
        glm::vec4(0.45f, 0.50f, 0.60f, 0.32f)
    );
}