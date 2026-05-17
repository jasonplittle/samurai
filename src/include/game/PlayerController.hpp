#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "Character.hpp"

struct InputState
{
    bool left;
    bool right;
    bool up;
    bool down;
    bool space;
};

class PlayerController
{
public:
    PlayerController(Character& player) : m_player(player) {};
    void Update(float dt, InputState inputState);

private:
    Character& m_player;

};