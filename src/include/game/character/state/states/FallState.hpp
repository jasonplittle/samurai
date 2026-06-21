#pragma once

#include "CharacterState.hpp"
#include "AirBourne.hpp"


class FallState : public CharacterState, public AirBourne
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Fall state" << std::endl;
        c.Animator().Play(Animation::Fall);

        c.Movement().AccelY = -c.Stats().FallGravity;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = AirBourneUpdate(c, dt);
        if (exit) return;

    }

    StateID GetID() const override
    {
        return StateID::Fall;
    }
};
