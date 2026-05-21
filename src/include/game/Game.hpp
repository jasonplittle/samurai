#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"
#include "CharacterAnimation.hpp"

#include "World.hpp"
#include "BackgroundParallax.hpp"

#include "SpriteRenderer.hpp"


class Game
{
public:
    Game();

    void Init();
    void Update(float dt);
    void Render();

private:
    Character m_player1;
    PlayerController m_player1Controller;
    InputState m_player1Input;
    CharacterAnimation m_player1Animator;
    
    Character m_player2;
    PlayerController m_player2Controller;
    InputState m_player2Input;
    CharacterAnimation m_player2Animator;

    PhysicsSystem m_physics;

    World m_world;
    BackgroundParallax m_background;

    OrthographicCamera m_camera;
    SpriteRenderer m_renderer;


};