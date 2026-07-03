#pragma once

#include "SpriteRenderer.hpp"
#include "QuadRenderer.hpp"
#include "Character.hpp"
#include "MobManager.hpp"


struct MobHealthBar
{
    float MaxHealth = 0;
    float DisplayHealth = 0;
    glm::vec2 BarPosition = glm::vec2(0, 0);
    glm::vec2 BarSize = glm::vec2(0, 0);
};


class GameHUD
{
public:
    void Update(float dt, Character& player, const MobManager& mobs);
    void DrawHUD(QuadRenderer& quadRenderer, OrthographicCamera camera);

private:
    float m_displayHealth = 0;
    float m_displayHealthMax = 0;

    float m_displayStamina = 0;
    float m_displayStaminaMax = 0;

    float m_displayMana = 0;
    float m_displayManaMax = 0;

    std::unordered_map<Character*, MobHealthBar> m_mobHealthBars;

};
