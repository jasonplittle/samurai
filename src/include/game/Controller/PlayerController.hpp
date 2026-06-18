#pragma once

#include <iostream>
#include <memory>
#include <queue>
#include <vector>

#include "GameInput.hpp"
#include "Character.hpp"


class PlayerController
{
public:
    PlayerController(std::shared_ptr<Character> player, GameInput& input) : m_player(player), m_input(input) {}
    void Update(float dt);

private:
    std::shared_ptr<Character> m_player;
    GameInput& m_input;
};
