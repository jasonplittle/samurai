#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "Character.hpp"

struct InputState
{
    bool up;
    bool down;
    bool left;
    bool right;
    bool ability;
};

class PlayerController
{
public:
    PlayerController(Character& player) : m_player(player) {};
    void Update(float dt, InputState inputState);

private:
    Character& m_player;

};