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
    int moveX = 0;

    if (inputState.right)
    {
        moveX = 1;
    }

    if (inputState.left)
    {
        moveX = -1;
    }

    if ((inputState.right && inputState.left))
    {
        moveX = 0;
    }


    CharacterIntent intent
    {
        .Jump = inputState.up,
        .Down = inputState.down,
        .Primary = inputState.ability,
        .Secondary = inputState.down,
        .MoveX = moveX,
    };

    player.SetIntent(intent);
}

// void PlayerController::Update(float dt)
// {
//     while (!m_commandQueue.Empty())
//     {
//         auto command = m_commandQueue.Pop();
//         command->Execute(m_player);
//     }
// }
