#pragma once

#include "ICharacterState.hpp"


class DashState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Dash state" << std::endl;
    }

    void Update(Character& c, float dt) override
    {
}

    StateID GetID() const override
    {
        return StateID::Dash;
    }
};
