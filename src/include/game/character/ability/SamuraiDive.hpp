#pragma once

#include "IAbility.hpp"


class SamuraiDive : public IAbility
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
        m_isActive = true;
        c.Animator().Play(Animation::Fall);
        c.StateMachine().RequestState(StateID::Attacking, c);
        c.Movement().AccelY = -c.Stats().FastFallGravity;
        c.Body().Velocity.y = 0;

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;        
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (c.Body().IsGrounded)
        {
            m_isActive = false;
            spawnHitbox(c);
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

private:
    void spawnHitbox(Character& c)
    {
        Hitbox hitbox = 
        {
            .PositionOffset = glm::vec2(0, -16),
            .Radii = glm::vec2(10, 3),
            .Damage = 3.f,
            .Knockback = 100.f,
            .Instigator = &c,
            .Lifetime = 0.2,
        };

        c.GameplayContext().SpawnHitbox(hitbox);
    }
};
