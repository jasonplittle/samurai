#pragma once

#include "IAbility.hpp"


class SamuraiDash : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.Body().IsGrounded)
            return true;

        return true;
    }

    void Activate(Character& c) override
    {
        std::cout << "Dash ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::Dash);
        c.StateMachine().RequestState(StateID::Attacking, c);
    
        c.Body().Velocity.x = 100 * c.IsFacingRight() ? -1 : 1;
    }

    void Update(Character& c, float dt) override
    {
        // if (!c.StateMachine().CheckState(StateID::Attacking))
        // {
        //     m_isActive = false;
        //     return;
        // }

        if(c.Animator().IsFinished())
        {
            m_isActive = false;
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
