#pragma once

#include "CharacterState.hpp"
#include "AirBourne.hpp"


class FloatState : public CharacterState, public AirBourne
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Float state" << std::endl;
        c.Animator().Play(Animation::Float);

        c.Movement().AccelY = -c.Stats().Gravity * 0.6;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = AirBourneUpdate(c, dt);
        if (exit) return;

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
