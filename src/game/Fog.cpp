#include "Fog.hpp"


void Fog::Update(float dt)
{
    m_time += dt;

    float windX =
        0.06f
        + 0.02f * std::sin(m_time * 0.11f)
        + 0.01f * std::sin(m_time * 0.37f)
        + 0.005f * std::sin(m_time * 0.91f);

    float windY =
        0.004f * std::sin(m_time * 0.21f)
        + 0.002f * std::sin(m_time * 0.73f);

    m_fogOffset += glm::vec2(windX, windY) * dt;
}

void Fog::DrawFog(NoiseRenderer& renderer, OrthographicCamera& camera) const
{
    renderer.Render(
        *m_fogSprite,
        camera,
        camera.Pos,
        camera.Size,
        glm::vec2(1.f, 1.f),
        (camera.Pos / camera.Size) + m_fogOffset,
        glm::vec4(0.45f, 0.50f, 0.60f, 0.32f)
    );
}