#pragma once

#include "IAbility.hpp"


class ExecutionerCleaveCombo : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

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
        if (m_attackPhase == 1 && c.Animator().GetCurrentFrame() > 10)
        {
            m_attackPhase = 2;
            m_nextPhaseRequesed = true;
            m_hitboxSpawned = false;
        }
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (m_attackPhase == 1)
        {
            if (!m_hitboxSpawned && c.Animator().GetCurrentFrame() > 7)
            {
                spawnHitbox(c);
            }
        }

        if (m_attackPhase == 2)
        {
            if (!m_hitboxSpawned && c.Animator().GetCurrentFrame() > 2)
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
            .Radii = glm::vec2(28, 28),
            .Damage = 30.f,
            .Knockback = 1000.f,
            .Instigator = &c,
            .LifetimeFrames = 2,
            .StartFrame = c.Animator().GetCurrentFrame()
        };

        m_hitbox = std::make_shared<Hitbox>(hitbox);
        c.GameplayContext().SpawnHitbox(m_hitbox);

        m_hitboxSpawned = true;
    }

private:
    int m_attackPhase = 0;
    bool m_nextPhaseRequesed = false;
    bool m_hitboxSpawned = false;

    std::shared_ptr<Hitbox> m_hitbox;

    // Move stats
};
