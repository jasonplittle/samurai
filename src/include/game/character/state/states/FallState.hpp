#pragma once

#include "IAirBourneState.hpp"


class FallState : public IAirBourneState
{
public:
    void OnEnter(Character& c) override
    {
        std::cout << "Fall state" << std::endl;
        c.Animator().Play(Animation::Fall);

        c.Movement().AccelY = -c.Stats().FallGravity;
    }

    void OnUpdate(Character& c, float dt) override
    {
    }

    StateID GetID() const override
    {
        return StateID::Fall;
    }
};
