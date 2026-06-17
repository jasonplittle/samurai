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

        if (c.Body().IsWalled && c.Stats().CanWallSlide)
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Fall;
    }
};
