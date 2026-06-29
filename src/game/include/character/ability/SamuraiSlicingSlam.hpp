#pragma once

#include "IAbility.hpp"


class SamuraiSlicingSlam : public IAbility
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
        std::cout << "Slicing slam ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::SpecialAttack);
        c.StateMachine().RequestState(StateID::Attacking, c);

        m_hitbox1 =
        {
            .PositionOffset = glm::vec2(18, 20),
            .Radii = glm::vec2(12, 40),
            .Damage = 40.f,
            .Knockback = 350.f,
            .Instigator = &c,
        };

        m_hitbox2 = 
        {
            .PositionOffset = glm::vec2(0, -c.Body().Radii.y),
            .Radii = glm::vec2(30, 5),
            .Damage = 10.f,
            .Knockback = 600.f,
            .Instigator = &c,
        };

        c.Movement().TargetSpeedX = 40;
        c.Movement().AccelY = -c.Stats().Gravity;
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (c.Animator().IsAfterFrame(6))
        {
            c.Movement().TargetSpeedX = c.Stats().RunSpeed;
            c.Movement().AccelX = c.Stats().RunAccel;
        }

        if (c.Animator().IsAfterFrame(10))
        {
            if (!c.Body().IsGrounded)
            {
                c.StateMachine().RequestState(StateID::Fall, c);
            }
        }

        manageHitbox1(c, 6, 8);
        manageHitbox2(c, 11, 13);

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

private:
    void manageHitbox1(Character& c, int spawnFrame, int despawnFrame)
    {
        if (!m_hitbox1Spawned && c.Animator().IsAfterFrame(spawnFrame))
        {
            m_hitbox = std::make_shared<Hitbox>(m_hitbox1);
            c.GameplayContext().SpawnHitbox(m_hitbox);

            m_hitbox1Spawned = true;
        }

        if (m_hitbox1Spawned && c.Animator().IsBeforeFrame(despawnFrame))
        {
            m_hitbox->KeepHitboxAlive();
        }
    }

    void manageHitbox2(Character& c, int spawnFrame, int despawnFrame)
    {
        if (!m_hitbox2Spawned && c.Animator().IsAfterFrame(spawnFrame))
        {
            m_hitbox = std::make_shared<Hitbox>(m_hitbox2);
            c.GameplayContext().SpawnHitbox(m_hitbox);

            m_hitbox2Spawned = true;
        }

        if (m_hitbox2Spawned && c.Animator().IsBeforeFrame(despawnFrame))
        {
            m_hitbox->KeepHitboxAlive();
        }
    }

private:
    std::shared_ptr<Hitbox> m_hitbox;
    bool m_hitbox1Spawned = false;
    bool m_hitbox2Spawned = false;

    Hitbox m_hitbox1;
    Hitbox m_hitbox2;
};
