#pragma once

#include "SpriteRenderer.hpp"
#include "QuadRenderer.hpp"


class GameHUD
{
public:

    void Update(float dt, float newHealthPerc);
    void DrawHUD(QuadRenderer& quadRenderer, OrthographicCamera camera);

private:
    float m_displayHealth = 0;

};
