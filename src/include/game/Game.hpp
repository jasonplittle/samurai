#pragma once

#include "Character.hpp"
#include "PlayerController.hpp"

#include "World.hpp"
#include "BackgroundParallax.hpp"

#include "SpriteRenderer.hpp"


struct Inputs
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool space;

    bool w;
    bool s;
    bool a;
    bool d;
    bool f;

    bool lMouse;
    bool rMouse;
    glm::vec2 mousePos;
};



class Game
{
public:
    Game();

    void Init();
    void ReadInput(glm::ivec2 windowSize, Inputs inputs);
    void Update(float dt);
    void Render();

private:
    std::unique_ptr<Character> m_player1;
    PlayerController m_playerController;
    InputState m_player1Input;

    
    // Character m_player2;
    // PlayerController m_player2Controller;
    // InputState m_player2Input;

    PhysicsSystem m_physics;

    World m_world;
    BackgroundParallax m_background;

    OrthographicCamera m_camera;
    SpriteRenderer m_renderer;




};