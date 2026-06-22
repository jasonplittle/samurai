#pragma once

#include "IAbility.hpp"


class SamuraiAirAttack : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

        if (c.Body().IsGrounded)
            return false;

        return true;
    }

    void Activate(Character& c) override
    {
        std::cout << "Air attack ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::AirAttack);
        c.StateMachine().RequestState(StateID::Attacking, c);
        c.Body().Velocity.y = 0;
        c.Movement().AccelY = 0;
        c.Movement().TargetSpeedX = 0;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        m_timeInPhase += dt;

        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        manageHitbox(c, 3, 5);

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
    bool m_hitboxSpawned = false;
    float m_timeInPhase = 0.0f;

    std::shared_ptr<Hitbox> m_hitbox;

};
