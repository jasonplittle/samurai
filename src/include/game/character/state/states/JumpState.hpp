#pragma once

#include "IAirBourneState.hpp"


class JumpState : public IAirBourneState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Jump state" << std::endl;
        c.Animator().Play(Animation::Jump);

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Body().Velocity.y = c.Stats().JumpVelocity;
    }

    void OnUpdate(Character& c, float dt) override
    {
        if (c.Body().Velocity.y < std::sqrt(0.15) * c.Stats().JumpVelocity)
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Jump;
    }
};
