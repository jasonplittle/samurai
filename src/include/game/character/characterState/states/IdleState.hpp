#pragma once

#include "CharacterState.hpp"


class IdleState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Idle state" << std::endl;
        c.Animator().Play(Animation::Idle);

        c.Movement().TargetSpeedX = c.Stats().WalkSpeed;
        c.Movement().AccelX = c.Stats().WalkAccel;
        c.Movement().DeccelX = c.Stats().WalkDeccel;
        c.Movement().AccelY = -c.Stats().Gravity;
    }

    void Update(Character& c, float dt) override
    {
        float speed = std::abs(c.Body().Velocity.x);

        if (!c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }

        if (c.Intent().Jump)
        {
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (speed > c.Stats().IdleSpeed || (c.Body().IsWalled && std::abs(c.Intent().MoveX) > 0))
        {
            c.StateMachine().RequestState(StateID::Walk, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Idle;
    }
};