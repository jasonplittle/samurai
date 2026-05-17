#include "PlayerController.hpp"


void PlayerController::Update(float dt, InputState inputState)
{
    if (inputState.space)
    {
        m_player.Attack();
    }
    if (inputState.up)
    {
        m_player.Jump();
    }
    if (inputState.down)
    {
        m_player.MoveDown();
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
}

// void PlayerController::Update(float dt)
// {
//     while (!m_commandQueue.Empty())
//     {
//         auto command = m_commandQueue.Pop();
//         command->Execute(m_player);
//     }
// }
