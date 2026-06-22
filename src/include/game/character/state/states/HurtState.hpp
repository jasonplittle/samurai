#pragma once

#include "ICharacterState.hpp"


class HurtState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Hurt state" << std::endl;
        c.Animator().Play(Animation::Hurt);

        c.Movement().AccelY = -c.Stats().FallGravity;
    }

    void Update(Character& c, float dt) override
    {
        c.Motor();

        if (c.Animator().IsFinished())
        {
            if (c.Health() <= 0.0)
            {
                c.StateMachine().RequestState(StateID::Death, c);
            }
            else
            {
                c.StateMachine().RequestState(StateID::Idle, c);
            }
        }
    }

    StateID GetID() const override
    {
        return StateID::Hurt;
    }
};
