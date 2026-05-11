#include "PlayerController.hpp"


void PlayerController::Update(float dt, InputState inputState)
{
    if (inputState.attack)
    {
        m_player.Attack();
    }
    if (inputState.jump)
    {
        m_player.Jump();
    }
    if (inputState.left)
    {
        m_player.MoveLeft();
    }
    if (inputState.right)
    {
        m_player.MoveRight();
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
