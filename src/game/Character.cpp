#include "Character.hpp"


Character::Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator, CharacterAbilities abilities, IGameplayContext& gameplayContext)
    : m_stats(stats), m_stateMachine(std::move(stateMachine)), m_animator(std::move(animator)), m_abilities(std::move(abilities)), m_gameplayContext(gameplayContext)
{
    m_body.Position = initPosition;
    m_body.Radii.x = m_stats.RadiusX;
    m_body.Radii.y = m_stats.RadiusY;

    m_health = m_stats.MaxHealth;

    m_movementProfile.AccelY = -m_stats.Gravity;

    m_stateMachine.RequestState(StateID::Idle, *this);
}

void Character::Motor()
{
    const float speedDif = (m_movementProfile.TargetSpeedX * ((m_currentIntent.MoveX > 0) - (m_currentIntent.MoveX < 0))) - m_body.Velocity.x;
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
}


void Character::Update(float dt, std::vector<Hitbox>& hitboxes)
{
    bool hit = applyHitboxes(hitboxes);
    
    if (hit)
    {
        m_stateMachine.RequestState(StateID::Hurt, *this);
    }
    else
    {
        if (m_currentIntent.Dash)
            m_abilities.RequestAbility(*this, AbilitySlot::Dash);

        if (m_currentIntent.Down.Pressed)
            m_abilities.RequestAbility(*this, AbilitySlot::Down);

        if (m_currentIntent.Primary.Pressed && m_body.IsGrounded)
            m_abilities.RequestAbility(*this, AbilitySlot::Primary);

        if (m_currentIntent.Primary.Pressed && !m_body.IsGrounded)
            m_abilities.RequestAbility(*this, AbilitySlot::AirPrimary);
    }

    m_animator.Update(dt);
    m_abilities.Update(*this, dt);
    m_stateMachine.Update(*this, dt);
}


bool Character::applyHitboxes(std::vector<Hitbox>& hitboxes)
{
    bool hit = false;

    for (auto& hitbox : hitboxes)
    {
        if (this == hitbox.Instigator)
            continue;

        if (hitbox.HitTargets.find(this) != hitbox.HitTargets.end())
            continue;

        if (!Intersects(hitbox.Bounds(), Hurtbox()))
            continue;

        hit = true;
        
        hitbox.HitTargets.insert(this);

        // Knockback
        glm::vec2 direction = glm::normalize(m_body.Position - hitbox.Instigator->Body().Position);
        direction.y *= 0.5;
        m_body.Velocity = direction * (hitbox.Knockback / m_stats.Mass);

        // Damage
        bool crit = (m_isFacingRight && direction.x > 0.0) || (!m_isFacingRight && direction.x < 0.0);
        m_health -= hitbox.Damage * (crit ? 1.4 : 1);
    }

    return hit;
}

Rect Character::Hurtbox() const
{
    return Rect 
    {
        m_body.Position.x - m_body.Radii.x,
        m_body.Position.y - m_body.Radii.y,
        m_body.Position.x + m_body.Radii.x,
        m_body.Position.y + m_body.Radii.y
    };
}
