#pragma once

#include "CharacterState.hpp"

class RunState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        c.Animator.Play("run");
    }

    void Update(Character& c, float dt) override
    {
        float speed = std::abs(c.Body.Velocity.x);

        if (!c.Body.IsGrounded)
        {
            c.StateMachine.RequestState(
                StateID::Fall,
                c);

            return;
        }

        if (speed <= 0.1f)
        {
            c.StateMachine.RequestState(
                StateID::Idle,
                c);

            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Run;
    }
};