#pragma once

#include "IAirBourneState.hpp"


class FloatState : public IAirBourneState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Float state" << std::endl;
        c.Animator().Play(Animation::Float);

        c.Movement().AccelY = -c.Stats().FloatGravity;
    }

    void OnUpdate(Character& c, float dt) override
    {
        if (c.Body().Velocity.y < 0 && c.Animator().IsFinished())
        {
            c.StateMachine().RequestState(StateID::Fall, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Float;
    }
};
