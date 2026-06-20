#pragma once

#include "CharacterState.hpp"


class Grounded
{
protected:
    bool GroundedUpdate(Character& c, float dt)
    {
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