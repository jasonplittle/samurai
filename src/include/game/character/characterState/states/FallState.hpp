#pragma once

#include "CharacterState.hpp"


class FallState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Fall state" << std::endl;
        c.Animator().Play(Animation::Fall);
    }

    void Update(Character& c, float dt) override
    {
        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Intent().Down)
        {
            c.Movement().AccelY = -c.Stats().FastFallGravity;
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Fall;
    }
};
