#pragma once

#include "CharacterState.hpp"
#include "Grounded.hpp"


class RunState : public CharacterState, public Grounded
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Run state" << std::endl;
        c.Animator().Play(Animation::Run);

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = GroundedUpdate(c, dt);
        if (exit) return;

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