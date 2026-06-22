#include "PlayerController.hpp"


void PlayerController::Update(float dt)
{
    CharacterIntent intent = {};

    
    if (m_input.Held(Action::MoveLeft))
    {
        intent.MoveX -= 1.0f;
    }

    if (m_input.Held(Action::MoveRight))
    {
        intent.MoveX += 1.0f;
    }

    if (m_input.DoublePressed(Action::MoveLeft) || m_input.DoublePressed(Action::MoveRight))
    {
        intent.Dash = true;
    }

    InputButton jump = 
    {
        .Pressed = m_input.Pressed(Action::Jump),
        .Released = m_input.Released(Action::Jump),
        .Held = m_input.Held(Action::Jump),
    };
    intent.Jump = jump;    

    InputButton down = 
    {
        .Pressed = m_input.Pressed(Action::Down),
        .Released = m_input.Released(Action::Down),
        .Held = m_input.Held(Action::Down),
    };
    intent.Down = down;

    InputButton defend = 
    {
        .Pressed = m_input.Pressed(Action::Down),
        .Released = m_input.Released(Action::Down),
        .Held = m_input.Held(Action::Down),
    };
    intent.Defend = defend;

    InputButton primary = 
    {
        .Pressed = m_input.Pressed(Action::Primary),
        .Released = m_input.Released(Action::Primary),
        .Held = m_input.Held(Action::Primary),
    };
    intent.Primary = primary;

    InputButton slow = 
    {
        .Pressed = m_input.Pressed(Action::Slow),
        .Released = m_input.Released(Action::Slow),
        .Held = m_input.Held(Action::Slow),
    };
    intent.Slow = slow;

    InputButton secondary = 
    {
        .Pressed = m_input.Pressed(Action::Secondary),
        .Released = m_input.Released(Action::Secondary),
        .Held = m_input.Held(Action::Secondary),
    };    
    intent.Secondary = secondary;

    m_player->SetIntent(intent);
}

// void PlayerController::Update(float dt)
// {
//     while (!m_commandQueue.Empty())
//     {
//         auto command = m_commandQueue.Pop();
//         command->Execute(m_player);
//     }
// }
