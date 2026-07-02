#pragma once

#include "ICharacterState.hpp"


class IGroundedState : public ICharacterState
{
public:
    void Enter(Character& c) override final
    {
        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().DoubleJumpUsed = false;
        c.Movement().DashUsed = false;

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;

        OnEnter(c);
    }

    void Update(Character& c, float dt) override final
    {
        bool exit = GroundedUpdate(c, dt);
        if (exit) return;

        OnUpdate(c, dt);
    }

protected:
    virtual void OnEnter(Character& c) {}
    virtual void OnUpdate(Character& c, float dt) = 0;

    bool GroundedUpdate(Character& c, float dt)
    {
        c.Motor();

        c.Stamina() += 2.f * dt;

        if (c.Stamina() > c.Stats().MaxStamina)
        {
            c.Stamina() = c.Stats().MaxStamina;
        }

        if (!c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return true;
        }

        if (c.Stats().CanJump && c.Intent().Jump.Held)
        {
            c.StateMachine().RequestState(StateID::Jump, c);
            return true;
        }

        if ((!c.Body().Walled.IsFree() && std::abs(c.Intent().MoveX) > 0))
        {
            c.StateMachine().RequestState(StateID::Walk, c);
            return true;
        }

        return false;
    }
};