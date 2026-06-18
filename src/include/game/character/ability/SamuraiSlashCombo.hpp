#pragma once

#include "IAbility.hpp"


class SamuraiSlashCombo : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (!c.Body().IsGrounded)
            return false;

        return true;
    }

    void Activate(Character& c) override
    {
        m_isActive = true;
        c.Animator().Play(Animation::Attack1);
        c.StateMachine().RequestState(StateID::Attacking, c);
        m_attackPhase = 1;
        m_hitboxSpawned = false;
    }

    void Trigger(Character& c) override
    {
        if (m_attackPhase == 1)
        {
            if (m_timeInPhase > 0.6)
            {
                m_attackPhase = 2;
                m_timeInPhase = 0.f;
                m_nextPhaseRequesed = true;
                m_hitboxSpawned = false;
            }
        }

        if (m_attackPhase == 2 && m_timeInPhase > 0.6)
        {
            m_attackPhase = 3;
            m_timeInPhase = 0.f;
            m_nextPhaseRequesed = true;
            m_hitboxSpawned = false;
        }
    }

    void Update(Character& c, float dt) override
    {
        m_timeInPhase += dt;

        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (m_attackPhase == 1)
        {
            if (!m_hitboxSpawned && m_timeInPhase > 0.4)
            {
                spawnHitbox(c);
            }
        }

        if (m_attackPhase == 2)
        {
            if (!m_hitboxSpawned && m_timeInPhase > 0.3)
            {
                spawnHitbox(c);
            }
        }

        if (m_attackPhase == 3)
        {
            if (!m_hitboxSpawned && m_timeInPhase > 0.2)
            {
                spawnHitbox(c);
            }
        }

        if (c.Animator().IsFinished())
        {
            if (!m_nextPhaseRequesed)
            {
                m_isActive = false;
                c.StateMachine().RequestState(StateID::Idle, c);
                return;
            }

            if (m_attackPhase == 2)
            {
                c.Animator().Play(Animation::Attack2);
                m_timeInPhase = 0.f;
                m_nextPhaseRequesed = false;
            }

            if (m_attackPhase == 3)
            {
                c.Animator().Play(Animation::Attack3);
                m_timeInPhase = 0.f;
                m_nextPhaseRequesed = false;
            }
        }        
    }

private:
    void spawnHitbox(Character& c)
    {
        Hitbox hitbox = 
        {
            .PositionOffset = glm::vec2(24, 0),
            .Radii = glm::vec2(16, 16),
            .Damage = 15.f * m_attackPhase,
            .Knockback = 500.f,
            .Instigator = &c,
            .Lifetime = 0.2,
        };

        c.GameplayContext().SpawnHitbox(hitbox);

        m_hitboxSpawned = true;
    }

private:
    int m_attackPhase = 0;
    float m_timeInPhase = 0.0f;
    bool m_nextPhaseRequesed = false;
    bool m_hitboxSpawned = false;


    // Move stats
};
