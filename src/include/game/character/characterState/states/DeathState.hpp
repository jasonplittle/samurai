#pragma once

#include "CharacterState.hpp"


class DeathState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Death state" << std::endl;
        c.Animator().Play(Animation::Death);

        c.Movement().TargetSpeedX = 0;
        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        if (c.Animator().IsFinished())
        {
            c.StateMachine().RequestState(StateID::Dead, c);
        }
    }

    virtual bool CanTransitionTo(StateID next, Character& c)
    {
        if (next != StateID::Dead)
            return false;

        return true;
    }

    StateID GetID() const override
    {
        return StateID::Death;
    }
};