#include "GameHUD.hpp"

#include <cmath>


static float EaseOut(float t)
{
    return 1.0f - (1.0f - t) * (1.0f - t);
}


void GameHUD::Update(float dt, float newHealthPerc)
{
    m_displayHealth = std::lerp(m_displayHealth, newHealthPerc, EaseOut(dt) * 2.f);
}


void GameHUD::DrawHUD(QuadRenderer& quadRenderer, OrthographicCamera camera)
{
    glm::vec2 barSize = glm::vec2(200, 10);

    float healthBarSize = barSize.x * m_displayHealth;
    if (healthBarSize < 0)
        healthBarSize = 0;

    glm::vec2 healthSize = glm::vec2(healthBarSize, 10);


    quadRenderer.Render(camera, camera.Pos + glm::vec2(-camera.Size.x * 0.5 + 5, camera.Size.y * 0.5 - barSize.y - 5), barSize, glm::vec4(0.15f, 0.15f, 0.15f, 1.0f));
    quadRenderer.Render(camera, camera.Pos + glm::vec2(-camera.Size.x * 0.5 + 5, camera.Size.y * 0.5 - barSize.y - 5), healthSize, glm::vec4(0.18f, 0.02f, 0.02f, 1.0f), glm::vec4(0.55f, 0.05f, 0.05f, 1.0f), glm::vec4(0.75f, 0.12f, 0.08f, 1.0f));
}
