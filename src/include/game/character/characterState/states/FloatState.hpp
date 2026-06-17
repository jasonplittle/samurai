#pragma once

#include "CharacterState.hpp"

// const float floatEnterThreshFactor = std::sqrt(0.25);
const float floatExitThreshFactor = std::sqrt(0.15);


class FloatState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Float state" << std::endl;
        c.Animator().Play(Animation::Float);

        c.Movement().AccelY = -c.Stats().FallGravity;
    }

    void Update(Character& c, float dt) override
    {
        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Body().IsWalled && c.Stats().CanWallSlide)
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }

        if (c.Body().Velocity.y < -floatExitThreshFactor * c.Stats().JumpVelocity)
        {
            c.StateMachine().RequestState(StateID::Fall, c);
        }
    }

    StateID GetID() const override
    {
        return StateID::Float;
    }
};
