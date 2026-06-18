#pragma once

#include "CharacterState.hpp"


class RunState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Run state" << std::endl;
        c.Animator().Play(Animation::Run);

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
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

        if (speed <= c.Stats().WalkSpeed) // && speed check
        {
            std::cout << c.Intent().MoveX << std::endl;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Run;
    }
};