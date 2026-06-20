#pragma once

#include "CharacterState.hpp"
#include "AirBourne.hpp"


class JumpState : public CharacterState, public AirBourne
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Jump state" << std::endl;
        c.Animator().Play(Animation::Jump);

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Body().Velocity.y = c.Stats().JumpVelocity;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = AirBourneUpdate(c, dt);
        if (exit) return;

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
