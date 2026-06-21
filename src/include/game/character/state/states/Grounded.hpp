#pragma once

#include "CharacterState.hpp"


class Grounded
{
protected:
    bool GroundedUpdate(Character& c, float dt)
    {
        if (c.Intent().Slow.Held)
        {
            c.Movement().TargetSpeedX = c.Stats().WalkSpeed * 0.7;
            c.Movement().AccelX = c.Stats().WalkAccel;
            c.Movement().DeccelX = c.Stats().WalkDeccel;
        }
        if (c.Intent().Slow.Released)
        {
            c.Movement().TargetSpeedX = c.Stats().RunSpeed;
            c.Movement().AccelX = c.Stats().RunAccel;
            c.Movement().DeccelX = c.Stats().RunDeccel;
        }

        c.Motor();

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

        if ((c.Body().Walled != 0 && std::abs(c.Intent().MoveX) > 0))
        {
            c.StateMachine().RequestState(StateID::Walk, c);
            return true;
        }

        return false;
    }
};