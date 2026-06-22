#pragma once

#include "IGroundedState.hpp"

class IdleState : public IGroundedState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Idle state" << std::endl;
        c.Animator().Play(Animation::Idle);
    }

    void OnUpdate(Character& c, float dt) override
    {
        float speed = std::abs(c.Body().Velocity.x);
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