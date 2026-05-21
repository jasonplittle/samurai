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
            bool can = c.StateMachine().RequestState(StateID::Idle, c);

            // std::cout << "Fall state: " << can << std::endl;

            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Fall;
    }
};
