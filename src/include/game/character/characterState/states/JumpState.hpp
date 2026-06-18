#pragma once

#include "CharacterState.hpp"


const float floatEnterThreshFactor = std::sqrt(0.25);


class JumpState : public CharacterState
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
        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Stats().CanWallSlide && c.Body().IsWalled)
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }

        if (c.Body().Velocity.y < floatEnterThreshFactor * c.Stats().JumpVelocity)
        {
            c.StateMachine().RequestState(StateID::Float, c);
        }

        if (c.Intent().Jump.Released)
        {
            c.Movement().AccelY = -c.Stats().FallGravity;
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Jump;
    }
};
