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
        if (m_attackPhase == 1 && c.Animator().IsAfterFrame(4))
        {
            m_attackPhase = 2;
            m_nextPhaseRequesed = true;
            m_hitboxSpawned = false;
            return;
        }

        if (m_attackPhase == 2 && c.Animator().IsAfterFrame(4))
        {
            m_attackPhase = 3;
            m_nextPhaseRequesed = true;
            m_hitboxSpawned = false;
            return;
        }
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (std::abs(c.Intent().MoveX) > 0 && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Stats().CanJump && c.Intent().Jump.Pressed && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        switch (m_attackPhase)
        {
            case 1:
                manageHitbox(c, 5, 7);
                break;
            case 2:
                manageHitbox(c, 4, 6);
                break;
            case 3:
                manageHitbox(c, 3, 5);
                break;
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
