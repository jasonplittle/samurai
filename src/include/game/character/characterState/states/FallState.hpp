#pragma once

#include "CharacterState.hpp"


class FallState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        c.Animator().Play(Animation::Idle);
    }

    void Update(Character& c, float dt) override
    {
        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);

            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Idle;
    }
};