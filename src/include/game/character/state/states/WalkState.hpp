#pragma once

#include "IGroundedState.hpp"


class WalkState : public IGroundedState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Walk state" << std::endl;
        c.Animator().Play(Animation::Walk);
    }

    void OnUpdate(Character& c, float dt) override
    {
        float speed = std::abs(c.Body().Velocity.x);
        
        if (speed < c.Stats().IdleSpeed)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
        else if (speed > c.Stats().WalkSpeed * 0.9 && c.Stats().CanRun)
        {
            c.StateMachine().RequestState(StateID::Run, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Walk;
    }
};