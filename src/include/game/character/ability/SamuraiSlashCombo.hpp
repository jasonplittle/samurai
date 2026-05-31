#pragma once

#include "IAbility.hpp"


class SamuraiSlashComboAbility : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (!c.Body().IsGrounded)
            return false;

        // if (c.IsStunned())
        //     return false;

        return true;
    }

    void Activate(Character& c) override
    {
        m_isActive = true;
        c.Animator().Play(Animation::Attack1);
        c.StateMachine().RequestState(StateID::Attacking, c);  


        // SpawnHitbox(c);

        
    }

    void Update(Character& c, float dt) override
    {
        m_activatedDelta += dt;
        if (c.Animator().IsFinished() || !c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
        }

    }

private:
    float m_activatedDelta = 0.0f;
    int m_attackPhase = 0;

    // Move stats

};
