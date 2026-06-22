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
            if (c.Animator().GetCurrentFrame() > 5)
            {
                m_attackPhase = 2;
                m_nextPhaseRequesed = true;
                m_hitboxSpawned = false;
            }
        }

        if (m_attackPhase == 2 && c.Animator().GetCurrentFrame() > 5)
        {
            m_attackPhase = 3;
            m_nextPhaseRequesed = true;
            m_hitboxSpawned = false;
        }
    }

    void Update(Character& c, float dt) override
    {
        m_timer += dt;

        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (std::abs(c.Intent().MoveX) > 0 && m_timer > k_cancelTime)
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Stats().CanJump && c.Intent().Jump.Pressed && m_timer > k_cancelTime)
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        

        if (m_attackPhase == 1)
        {
            if (!m_hitboxSpawned && c.Animator().GetCurrentFrame() > 4)
            {
                spawnHitbox(c);
            }
        }

        if (m_attackPhase == 2)
        {
            if (!m_hitboxSpawned && c.Animator().GetCurrentFrame() > 3)
            {
                spawnHitbox(c);
            }
        }

        if (m_attackPhase == 3)
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

            if (m_attackPhase == 3)
            {
                c.Animator().Play(Animation::Attack3);
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
            .LifetimeFrames = 2,
            .StartFrame = c.Animator().GetCurrentFrame()
        };

        m_hitbox = std::make_shared<Hitbox>(hitbox);
        c.GameplayContext().SpawnHitbox(m_hitbox);

        m_hitboxSpawned = true;
    }

private:
    float m_timer = 0.0;
    const float k_cancelTime = 0.1;
    int m_attackPhase = 0;
    bool m_nextPhaseRequesed = false;
    bool m_hitboxSpawned = false;

    std::shared_ptr<Hitbox> m_hitbox;


    // Move stats
};
