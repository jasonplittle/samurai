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

void PlayerController::Update(float dt, Character& player, InputState inputState)
{
    if (inputState.ability)
    {
        player.AbilityPrimary();
    }
    if (inputState.up)
    {
        player.MoveUp();
    }
    if (inputState.left)
    {
        // std::cout << "Move" << std::endl;
        player.MoveLeft();
    }
    if (inputState.right)
    {
        // std::cout << "Move" << std::endl;
        player.MoveRight();
    }
    if (!inputState.right && !inputState.left)
    {
        // std::cout << "Idle" << std::endl;
        player.Idle();
    }
    if (inputState.down)
    {
        player.MoveDown();
        player.AbilitySecondary();
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
