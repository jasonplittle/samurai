#pragma once

#include "CharacterState.hpp"


class FallState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Fall state" << std::endl;
        c.Animator().Play(Animation::Fall);
        
        c.Movement().AccelY = -c.Stats().Gravity;
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
        return StateID::Fall;
    }
};
