#pragma once

#include "IAbility.hpp"


class SamuraiSlashCombo : public IAbility
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
        std::cout << "Samurai slash ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::Attack1);
        c.StateMachine().RequestState(StateID::Attacking, c);
        m_attackPhase = 1;
    }

    void Trigger(Character& c) override
    {
        if (m_attackPhase == 1 && c.Animator().IsAfterFrame(4))
        {
            m_attackPhase = 2;
            m_nextPhaseRequesed = true;
            return;
        }

        if (m_attackPhase == 2 && c.Animator().IsAfterFrame(3))
        {
            m_attackPhase = 3;
            m_nextPhaseRequesed = true;
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

        if (std::abs(c.Intent().MoveX) > 0 && c.Animator().IsAfterFrame(3))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }     

        if (c.Intent().Jump.Pressed && c.Animator().IsAfterFrame(2))
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
                m_hitboxSpawned = false;
            }

            if (m_attackPhase == 3)
            {
                c.Animator().Play(Animation::Attack3);
                m_nextPhaseRequesed = false;
                m_hitboxSpawned = false;
            }
        }        
    }

private:
    void spawnHitbox(Character& c)
    {
        std::shared_ptr<Hitbox> hitbox = std::make_shared<Hitbox>(
        Hitbox {
            .PositionOffset = glm::vec2(24, 0),
            .Radii = glm::vec2(16, 16),
            .Damage = 15.f * m_attackPhase,
            .Knockback = 500.f,
            .Instigator = &c,
        });

        m_hitboxes.push_back(hitbox);
        c.GameplayContext().SpawnHitbox(hitbox);
    }

    void manageHitbox(Character& c, int spawnFrame, int despawnFrame)
    {
        if (!m_hitboxSpawned && c.Animator().IsAfterFrame(spawnFrame))
        {
            spawnHitbox(c);
            m_hitboxSpawned = true;
        }

        if (m_hitboxSpawned && c.Animator().IsBeforeFrame(despawnFrame))
        {
            m_hitboxes.back()->KeepHitboxAlive();
        }
    }

private:
    int m_attackPhase = 0;
    bool m_nextPhaseRequesed = false;
    bool m_hitboxSpawned = false;

    std::vector<std::shared_ptr<Hitbox>> m_hitboxes;
};
