#pragma once

#include "CharacterState.hpp"


class DashState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Dash state" << std::endl;
    }

    void Update(Character& c, float dt) override
    {
        if (c.Stats().CanJump && c.Intent().Jump.Held && c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Jump, c);
            c.Movement().TargetSpeedX = c.Body().Velocity.x;
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Dash;
    }
};
