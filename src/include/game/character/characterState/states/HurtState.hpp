#pragma once

#include "CharacterState.hpp"


class HurtState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Hurt state" << std::endl;
        c.Animator().Play(Animation::Hurt);
    }

    void Update(Character& c, float dt) override
    {
        if (c.Animator().IsFinished())
        {
            c.StateMachine().RequestState(StateID::Idle, c);
        }
    }

    StateID GetID() const override
    {
        return StateID::Hurt;
    }
};
