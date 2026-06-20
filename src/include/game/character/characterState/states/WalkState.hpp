#pragma once

#include "CharacterState.hpp"
#include "Grounded.hpp"


class WalkState : public CharacterState, public Grounded
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Walk state" << std::endl;
        c.Animator().Play(Animation::Walk);

        c.Movement().TargetSpeedX = c.Stats().WalkSpeed;
        c.Movement().AccelX = c.Stats().WalkAccel;
        c.Movement().DeccelX = c.Stats().WalkDeccel;
    }

    void Update(Character& c, float dt) override
    {
        bool exit = GroundedUpdate(c, dt);
        if (exit) return;

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