#pragma once

#include "IAbility.hpp"


class SamuraiDefend : public IAbility
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
        c.Animator().Play(Animation::Defend);
        c.StateMachine().RequestState(StateID::Attacking, c);
        c.Defence() = 0.7;
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            c.Defence() = 0.0f;
            return;
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.Defence() = 0.0f;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

};
