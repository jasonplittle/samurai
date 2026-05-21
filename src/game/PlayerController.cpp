#include "PlayerController.hpp"


// player input
// movement intentions
// jump logic - coyote timer, jump before hitting the ground
// dash logic
// coyote time
// jump buffering

// Jump design
    // coyote timer
    // Jump buffering
    // Press down to increase gravity
    // Variable jump height

void PlayerController::Update(float dt, InputState inputState)
{
    if (inputState.ability)
    {
        m_player.Attack();
    }
    if (inputState.up)
    {
        m_player.Jump();
    }
    if (inputState.left)
    {
        // std::cout << "Move" << std::endl;
        m_player.MoveLeft();
    }
    if (inputState.right)
    {
        // std::cout << "Move" << std::endl;
        m_player.MoveRight();
    }
    if (!inputState.right && !inputState.left)
    {
        // std::cout << "Idle" << std::endl;
        m_player.Idle();
    }
    if (inputState.down)
    {
        m_player.MoveDown();
        m_player.Defend();
    }
}

// void PlayerController::Update(float dt)
// {
//     while (!m_commandQueue.Empty())
//     {
//         auto command = m_commandQueue.Pop();
//         command->Execute(m_player);
//     }
// }
