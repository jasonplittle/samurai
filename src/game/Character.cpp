#include "Character.hpp"

#include <iostream>

Character::Character(glm::vec2 position, glm::vec2 size, float mass)
    : m_state(CharacterState::Idle)
{
    m_transform.Position = position;
    m_collider.Size = size;
    m_collider.HalfSize = size * 0.5f;
    m_rigidbody.Mass = mass;
}


void Character::Update(float dt, bool animationFinished)
{
    float speedDiff = m_targetSpeed - m_rigidbody.Velocity.x;
    m_rigidbody.Velocity.x += speedDiff * m_acc * dt;
    m_transform.Position += m_rigidbody.Velocity * dt;

    std::cout << m_rigidbody.Velocity.x << std::endl;



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
