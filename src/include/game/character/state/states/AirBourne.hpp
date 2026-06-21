#pragma once

#include "CharacterState.hpp"


class AirBourne
{
protected:
    bool AirBourneUpdate(Character& c, float dt)
    {
        c.Motor();

        if (c.Body().IsGrounded)
        {
            c.Movement().DoubleJumpUsed = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return true;
        }

        if (c.Stats().CanDoubleJump && c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed)
        {
            c.Movement().DoubleJumpUsed = true; // Todo Why? - stuart, fuck you
            c.StateMachine().RequestState(StateID::Jump, c);
            return true;
        }

        if (c.Stats().CanWallSlide && c.Body().Walled != 0)
        {
            c.Movement().DoubleJumpUsed = false;
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