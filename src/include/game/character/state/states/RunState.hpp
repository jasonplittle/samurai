#pragma once

#include "IGroundedState.hpp"


class RunState : public IGroundedState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Run state" << std::endl;
        c.Animator().Play(Animation::Run);
    }

    void OnUpdate(Character& c, float dt) override
    {
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