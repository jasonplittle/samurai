#include "Character.hpp"

#include <iostream>

Character::Character(glm::vec2 position, glm::vec2 size)
    : m_state(CharacterState::Idle), m_body{.Position = position, .Radii = size * 0.5f, }
{
    m_body.Position = position;
    m_body.Radii = size * 0.5f;
    m_body.UseGravity = true;
    // m_body.UseGravity = true;
}


void Character::Update(float dt, bool animationFinished)
{
    // float speedDiff = m_targetSpeed - m_body.Velocity.x;
    // m_body
    // m_rigidbody.Velocity.x += speedDiff * m_acc * dt;

    // std::cout << m_body.Velocity.x << std::endl;



    switch(m_state)
    {
        case CharacterState::Attack:
        {
            if (animationFinished)
            {
                m_state = CharacterState::Idle;
            }
            break;
        }
        case CharacterState::Jump:
        {
            if (animationFinished)
            {
                m_state = CharacterState::Idle;
            }

            break;
        }
    }
}
