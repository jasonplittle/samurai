#include "GameHUD.hpp"

#include <cmath>


static float EaseOut(float t)
{
    return 1.0f - (1.0f - t) * (1.0f - t);
}


void GameHUD::Update(float dt, Character& player, const MobManager& mobs)
{
    float newHealthPerc = player.Health() / player.Stats().MaxHealth;
    m_displayHealth = std::lerp(m_displayHealth, newHealthPerc, EaseOut(dt) * 2);
    m_displayHealthMax = player.Stats().MaxHealth;

    float newStaminaPerc = player.Stamina() / player.Stats().MaxStamina;
    m_displayStamina = std::lerp(m_displayStamina, newStaminaPerc, EaseOut(dt) * 2);
    m_displayStaminaMax = player.Stats().MaxStamina;

    float newManaPerc = player.Mana() / player.Stats().MaxMana;
    m_displayMana = std::lerp(m_displayMana, newManaPerc, EaseOut(dt) * 2);
    m_displayManaMax = player.Stats().MaxMana;

    for (auto& mobStruct : mobs.Mobs())
    {
        Character& mob = *mobStruct.Character; 

        m_mobHealthBars[&mob];

        if (!mob.IsAlive())
        {
            m_mobHealthBars.erase(&mob);
            continue;
        }

        float newMobHealthPerc = mob.Health() / mob.Stats().MaxHealth;
        m_mobHealthBars[&mob].MaxHealth = mob.Stats().MaxHealth;
        m_mobHealthBars[&mob].DisplayHealth = std::lerp(m_mobHealthBars[&mob].DisplayHealth, newMobHealthPerc, EaseOut(dt) * 2);

        m_mobHealthBars[&mob].BarSize = glm::vec2(mob.Stats().MaxHealth * 0.5, 3);
        
        m_mobHealthBars[&mob].BarPosition.x = mob.Body().Position.x - (m_mobHealthBars[&mob].BarSize.x * 0.5);
        m_mobHealthBars[&mob].BarPosition.y = mob.Body().Position.y + mob.Body().Radii.y + 5;
    }

}


void GameHUD::DrawHUD(QuadRenderer& quadRenderer, OrthographicCamera camera)
{
    for (auto& [mob, mobHealthBar] : m_mobHealthBars)
    {
        float mobHealthBarFill = mobHealthBar.BarSize.x * mobHealthBar.DisplayHealth;
        if (mobHealthBarFill < 0)
            mobHealthBarFill = 0;
        glm::vec2 healthFillSize = glm::vec2(mobHealthBarFill, mobHealthBar.BarSize.y);

        quadRenderer.Render(camera, mobHealthBar.BarPosition, mobHealthBar.BarSize, glm::vec4(0.12f, 0.12f, 0.13f, 1.0f));
        quadRenderer.Render(camera, mobHealthBar.BarPosition, healthFillSize, glm::vec4(0.18f, 0.02f, 0.02f, 1.0f), glm::vec4(0.55f, 0.05f, 0.05f, 1.0f), glm::vec4(0.75f, 0.12f, 0.08f, 1.0f));
        
    }

    glm::vec2 healthBarSize = glm::vec2(m_displayHealthMax * 2, 10);
    glm::vec2 healthBarPosition = camera.Pos + glm::vec2(-camera.Size.x * 0.5 + 5, camera.Size.y * 0.5 - healthBarSize.y - 5);
    float healthBarFill = healthBarSize.x * m_displayHealth;
    if (healthBarFill < 0)
        healthBarFill = 0;
    glm::vec2 healthFillSize = glm::vec2(healthBarFill, healthBarSize.y);

    quadRenderer.Render(camera, healthBarPosition, healthBarSize, glm::vec4(0.12f, 0.12f, 0.13f, 1.0f));
    quadRenderer.Render(camera, healthBarPosition, healthFillSize, glm::vec4(0.18f, 0.02f, 0.02f, 1.0f), glm::vec4(0.55f, 0.05f, 0.05f, 1.0f), glm::vec4(0.75f, 0.12f, 0.08f, 1.0f));

    
    glm::vec2 staminaBarSize = glm::vec2(m_displayStaminaMax * 1.5, 10);
    glm::vec2 staminaBarPosition = camera.Pos + glm::vec2(-camera.Size.x * 0.5 + 5, camera.Size.y * 0.5 - staminaBarSize.y - healthBarSize.y - 7);
    float staminaBarFill = staminaBarSize.x * m_displayStamina;
    if (staminaBarFill < 0)
        staminaBarFill = 0;
    glm::vec2 staminaFillSize = glm::vec2(staminaBarFill, staminaBarSize.y);

    quadRenderer.Render(camera, staminaBarPosition, staminaBarSize, glm::vec4(0.12f, 0.12f, 0.13f, 1.0f));
    quadRenderer.Render(camera, staminaBarPosition, staminaFillSize, glm::vec4(0.18f, 0.26f, 0.08f, 1.0f), glm::vec4(0.45f, 0.62f, 0.18f, 1.0f), glm::vec4(0.65f, 0.80f, 0.28f, 1.0f));

    glm::vec2 manaBarSize = glm::vec2(m_displayManaMax * 1, 10);
    glm::vec2 manaBarPosition = camera.Pos + glm::vec2(-camera.Size.x * 0.5 + 5, camera.Size.y * 0.5 - manaBarSize.y - staminaBarSize.y - healthBarSize.y - 10);
    float manaBarFill = manaBarSize.x * m_displayMana;
    if (manaBarFill < 0)
        manaBarFill = 0;
    glm::vec2 manaFillSize = glm::vec2(manaBarFill, manaBarSize.y);

    quadRenderer.Render(camera, manaBarPosition, manaBarSize, glm::vec4(0.12f, 0.12f, 0.13f, 1.0f));
    quadRenderer.Render(camera, manaBarPosition, manaFillSize, glm::vec4(0.05f, 0.18f, 0.38f, 1.0f), glm::vec4(0.18f, 0.48f, 0.78f, 1.0f), glm::vec4(0.35f, 0.70f, 0.95f, 1.0f));
}
