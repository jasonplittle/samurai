#include "Character.hpp"


Character::Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator, CharacterAbilities abilities)
    : m_stats(stats), m_stateMachine(std::move(stateMachine)), m_animator(std::move(animator)), m_abilities(std::move(abilities))
{
    m_body.Position = initPosition;
    m_body.Radii.x = m_stats.RadiusX;
    m_body.Radii.y = m_stats.RadiusY;

    m_movementProfile.AccelY = -m_stats.Gravity;

    m_stateMachine.RequestState(StateID::Idle, *this);
}


void Character::Update(float dt)
{
    const float speedDif = (m_movementProfile.TargetSpeedX * m_currentIntent.MoveX) - m_body.Velocity.x;
    m_body.Acceleration.x = speedDif * (std::abs(m_currentIntent.MoveX) > 0 ? m_movementProfile.AccelX : m_movementProfile.DeccelX);

    m_body.Acceleration.y = m_movementProfile.AccelY;
    
    if (m_currentIntent.MoveX > 0)
    {
        m_isFacingRight = true;
    }
    if (m_currentIntent.MoveX < 0)
    {
        m_isFacingRight = false;
    }

    if (m_currentIntent.Jump && m_stats.JumpVelocity == 0)
    {
        m_currentIntent.Jump = false;
    }

    if (m_currentIntent.Primary)
    {
        m_abilities.RequestAbility(*this, AbilitySlot::Primary);
    }

    m_animator.Update(dt);
    m_abilities.Update(*this, dt);
    m_stateMachine.Update(*this, dt);
}
