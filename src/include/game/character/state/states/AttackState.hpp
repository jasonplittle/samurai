#pragma once

#include "ICharacterState.hpp"


class AttackState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Attack state" << std::endl;

        c.Movement().TargetSpeedX = 0;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        c.Motor();
    }

    StateID GetID() const override
    {
        return StateID::Attacking;
    }
};