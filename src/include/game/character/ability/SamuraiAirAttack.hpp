#pragma once

#include "IAbility.hpp"


class SamuraiAirAttack : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.Body().IsGrounded)
            return false;

        // if (c.IsStunned())
        //     return false;

        return true;
    }

    void Activate(Character& c) override
    {
        m_isActive = true;
        c.Animator().Play(Animation::AirAttack);
        c.StateMachine().RequestState(StateID::Attacking, c);

        // c.Movement().AccelY = 0;
    }

    void Update(Character& c, float dt) override
    {
        m_timeInPhase += dt;

        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (!m_hitboxSpawned && m_timeInPhase > 0.2)
        {
            spawnHitbox(c);
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
    }

private:
    void spawnHitbox(Character& c)
    {
        Hitbox hitbox = 
        {
            .PositionOffset = glm::vec2(20, 0),
            .Radii = glm::vec2(16, 12),
            .Damage = 15.f,
            .Knockback = 250.f,
            .Instigator = &c,
            .Lifetime = 0.2,
        };

        c.GameplayContext().SpawnHitbox(hitbox);

        m_hitboxSpawned = true;
    }

private:
    bool m_hitboxSpawned = false;
    float m_timeInPhase = 0.0f;

    // Move stats
};
