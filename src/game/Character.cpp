#include "Character.hpp"


Character::Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, AnimationSetPlayer animator, CharacterAbilities abilities, IGameplayContext& gameplayContext)
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


void Character::Update(float dt, const HitboxManager& hitboxManager)
{
    bool hit = applyHitboxes(hitboxManager);
    
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

        if (m_currentIntent.Defend.Pressed)
            m_abilities.RequestAbility(*this, AbilitySlot::Defend);

        if (m_currentIntent.Primary.Pressed)
        {
            m_abilities.RequestAbility(*this, AbilitySlot::Primary);
            m_abilities.RequestAbility(*this, AbilitySlot::AirPrimary);
        }
        if (m_currentIntent.Secondary.Pressed)
        {
            m_abilities.RequestAbility(*this, AbilitySlot::Secondary);
        }
    }

    m_animator.Update(dt);
    m_abilities.Update(*this, dt);
    m_stateMachine.Update(*this, dt);
}


bool Character::applyHitboxes(const HitboxManager& hitboxManager)
{
    bool hit = false;

    for (const auto& hitbox : hitboxManager.GetHitboxes())
    {
        if (this == hitbox->Instigator)
            continue;

        if (hitbox->HitTargets.find(this) != hitbox->HitTargets.end())
            continue;

        if (!Intersects(hitbox->Bounds(), Hurtbox()))
            continue;

        bool hitboxDefended = m_defence * 100.f >= hitbox->Damage;
        if (!hit && !hitboxDefended) hit = true;
        
        hitbox->HitTargets.insert(this);

        glm::vec2 direction = glm::normalize(m_body.Position - hitbox->Instigator->Body().Position);
        direction.y *= 0.5;
        m_body.Velocity = direction * (hitbox->Knockback / m_stats.Mass) * (hitboxDefended ? m_defence : 1.0f);

        // Damage
        bool crit = (m_isFacingRight && direction.x > 0.0) || (!m_isFacingRight && direction.x < 0.0);
        m_health -= hitbox->Damage * (crit ? 1.4 : 1) * (hitboxDefended ? 1.f - m_defence : 1.0f);

        if (m_health <= 0.f) hit = true;
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
