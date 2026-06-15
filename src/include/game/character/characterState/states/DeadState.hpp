#pragma once

#include "CharacterState.hpp"


class DeadState : public CharacterState
{
public:
    virtual void Enter(Character& c) override
    {
        std::cout << "Dead state" << std::endl;
        c.Animator().Play(Animation::Dead);

        c.Movement().TargetSpeedX = 0;
        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    virtual void Update(Character& c, float dt) override
    {
        if (c.DeathDecay() > 0.5)
            c.DeathDecay() -= dt;
    }

    virtual bool CanTransitionTo(StateID next, Character& c)
    {
        return false;
    }

    virtual StateID GetID() const override
    {
        return StateID::Dead;
    }
};