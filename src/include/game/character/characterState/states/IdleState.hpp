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
    }

    void Update(Character& c, float dt) override
    {
        float speed = std::abs(c.Body().Velocity.x);

        if (!c.Body().IsGrounded)
        {
            // if (c.Stats())
            // {
                c.StateMachine().RequestState(StateID::Fall, c);
            // }
            
            return;
        }

        if (speed > c.Stats().IdleSpeed)
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