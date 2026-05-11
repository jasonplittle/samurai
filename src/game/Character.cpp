#include "Character.hpp"


void Character::Update(float dt, bool animationFinished)
{
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