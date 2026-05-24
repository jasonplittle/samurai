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
    bool primary;
};

class PlayerController
{
public:
    void Update(float dt, Character& player, InputState inputState);

private:

};