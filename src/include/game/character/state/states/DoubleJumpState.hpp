#pragma once

#include "CharacterState.hpp"
#include "AirBourne.hpp"


class DoubleJumpState : public CharacterState, public AirBourne
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Double jump state" << std::endl;
        c.Animator().Play(Animation::Jump);

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Body().Velocity.y = c.Stats().JumpVelocity;

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = AirBourneUpdate(c, dt);
        if (exit) return;

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
