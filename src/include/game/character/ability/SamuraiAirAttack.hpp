#pragma once

#include "IAbility.hpp"


class SamuraiAirAttack : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.Body().IsGrounded)
            return false;

        // if (c.IsStunned())
        //     return false;

        return true;
    }

    void Activate(Character& c) override
    {
        m_isActive = true;
        c.Animator().Play(Animation::AirAttack);
        c.StateMachine().RequestState(StateID::Attacking, c);

        // c.Movement().AccelY = 0;


        // SpawnHitbox(c);
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }        
    }

private:

    // Move stats
};
