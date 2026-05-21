#pragma once

#include "CharacterState.hpp"

class RunState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        c.Animator().Play(Animation::Walk);
    }

    void Update(Character& c, float dt) override
    {
        if (!c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Fall, c);
            return;
        }

        float speed = std::abs(c.Body().Velocity.x);
        if (speed <= c.Stats().WalkSpeed)
        {
            c.StateMachine().RequestState(StateID::Walk, c);

            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Run;
    }
};