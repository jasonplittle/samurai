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

void PlayerController::Update(float dt)
{
    CharacterIntent intent = {};

    if (m_input.DoublePressed(Action::MoveLeft))
    {
        intent.MoveX -= 2.0f;
    } 
    else if (m_input.Held(Action::MoveLeft))
    {
        intent.MoveX -= 1.0f;
    }

    if (m_input.DoublePressed(Action::MoveRight))
    {
        intent.MoveX += 2.0f;
    }
    else if (m_input.Held(Action::MoveRight))
    {
        intent.MoveX += 1.0f;
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

    InputButton primary = 
    {
        .Pressed = m_input.Pressed(Action::Primary),
        .Released = m_input.Released(Action::Primary),
        .Held = m_input.Held(Action::Primary),
    };
    intent.Primary = primary;

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
