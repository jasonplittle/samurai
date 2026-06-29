#pragma once

#include "ICharacterState.hpp"


class IAirBourneState : public ICharacterState
{
public:
    void Enter(Character& c) override final
    {
        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;

        OnEnter(c);
    }

    void Update(Character& c, float dt) override final
    {
        bool exit = AirBourneUpdate(c, dt);
        if (exit) return;

        OnUpdate(c, dt);
    }

protected:
    virtual void OnEnter(Character& c) {}
    virtual void OnUpdate(Character& c, float dt) = 0;

    bool AirBourneUpdate(Character& c, float dt)
    {
        c.Motor();

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return true;
        }

        if (c.Stats().CanDoubleJump && c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed)
        {
            c.StateMachine().RequestState(StateID::DoubleJump, c);
            return true;
        }

        if (c.Stats().CanWallSlide && c.Body().Walled.IsFull())
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return true;
        }

        if (!c.Intent().Jump.Held)
        {
            c.Movement().AccelY = -c.Stats().FallGravity;
        }

        return false;
    }
};
