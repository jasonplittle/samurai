#pragma once

#include "CharacterState.hpp"

class WalkState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Walk state" << std::endl;
        c.Animator().Play(Animation::Walk);

        c.Movement().TargetSpeedX = c.Stats().WalkSpeed;
        c.Movement().AccelX = c.Stats().WalkAccel;
        c.Movement().DeccelX = c.Stats().WalkDeccel;
    }

    void Update(Character& c, float dt) override
    {
        float speed = std::abs(c.Body().Velocity.x);

        if (!c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }

        if (c.Intent().Jump.Held)
        {
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (std::abs(c.Intent().MoveX) > 1.f)
        {
            c.StateMachine().RequestState(StateID::Run, c);
            return;
        }

        if (speed < c.Stats().IdleSpeed)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Walk;
    }
};