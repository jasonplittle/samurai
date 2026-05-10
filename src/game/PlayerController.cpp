#include "PlayerController.hpp"


void PlayerController::Update(float dt)
{

    while (!m_commandQueue.Empty())
    {
        auto command = m_commandQueue.Pop();
        command->Execute(m_player);
    }
}