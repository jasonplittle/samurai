#pragma once

#include "IAirBourneState.hpp"


class DoubleJumpState : public IAirBourneState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Double jump state" << std::endl;
        c.Animator().Play(Animation::Jump);

        c.Movement().DoubleJumpUsed = true;

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Body().Velocity.y = c.Stats().JumpVelocity;
    }

    void OnUpdate(Character& c, float dt) override
    {
        if (c.Body().Velocity.y < std::sqrt(0.1) * c.Stats().JumpVelocity)
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::DoubleJump;
    }
};
