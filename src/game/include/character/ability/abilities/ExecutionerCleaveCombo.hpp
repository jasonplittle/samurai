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
    }

    void Trigger(Character& c) override
    {
        if (m_attackPhase == 1 && c.Animator().IsAfterFrame(9))
        {
            m_attackPhase = 2;
            m_nextPhaseRequesed = true;
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
            manageHitbox(c, 8, 9);
        }

        if (m_attackPhase == 2)
        {
            manageHitbox(c, 3, 5);
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
                m_hitboxSpawned = false;
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
        };

        m_hitbox = std::make_shared<Hitbox>(hitbox);
        c.GameplayContext().SpawnHitbox(m_hitbox);

        m_hitboxSpawned = true;
    }

    void manageHitbox(Character& c, int spawnFrame, int despawnFrame)
    {
        if (!m_hitboxSpawned && c.Animator().IsAfterFrame(spawnFrame))
        {
            spawnHitbox(c);
        }

        if (m_hitboxSpawned && c.Animator().IsBeforeFrame(despawnFrame))
        {
            m_hitbox->KeepHitboxAlive();
        }
    }

private:
    int m_attackPhase = 0;
    bool m_nextPhaseRequesed = false;
    bool m_hitboxSpawned = false;

    std::shared_ptr<Hitbox> m_hitbox;
};
