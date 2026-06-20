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

        if (c.Stats().CanWallSlide && c.Body().IsWalled)
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