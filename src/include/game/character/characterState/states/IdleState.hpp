#pragma once

#include "CharacterState.hpp"


class IdleState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        c.Animator.Play(Animation::Idle);
    }

    void Update(Character& c, float dt) override
    {
        float speed = std::abs(c.Body.Velocity.x);

        if (!c.Body.IsGrounded)
        {
            c.StateMachine.RequestState(StateID::Fall, c);
            return;
        }

        if (speed > c.S)
        {
            c.StateMachine.RequestState(
                StateID::Run,
                c);

            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Idle;
    }
};