#pragma once

#include "SpriteRenderer.hpp"
#include "QuadRenderer.hpp"
#include "Character.hpp"


class GameHUD
{
public:

    void Update(float dt, Character& player);
    void DrawHUD(QuadRenderer& quadRenderer, OrthographicCamera camera);

private:
    float m_displayHealth = 0;
    float m_displayHealthMax = 0;

    float m_displayStamina = 0;
    float m_displayStaminaMax = 0;

    float m_displayMana = 0;
    float m_displayManaMax = 0;

};
