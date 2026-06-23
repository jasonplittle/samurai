#pragma once

#include "ICharacterState.hpp"


class WallSlideState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall state" << std::endl;

        if (c.Body().Walled.IsRight())
        {
            c.Animator().Play(Animation::WallContactRight);
            c.IsFacingRight() = false;
            c.Movement().AccelX = 1;
        }
        else if (c.Body().Walled.IsLeft())
        {
            c.Animator().Play(Animation::WallContactLeft);
            c.IsFacingRight() = true;
            c.Movement().AccelX = -1;
        }

        c.Body().Velocity.y = 0;
        c.Body().Velocity.x = 0;
        c.Movement().AccelY = 0;
        c.Movement().DoubleJumpUsed = false;
    }

    void Update(Character& c, float dt) override
    {
        c.Body().Acceleration.x = c.Movement().AccelX;
        c.Body().Acceleration.y = c.Movement().AccelY;

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Intent().Jump.Pressed)
        {
            c.StateMachine().RequestState(StateID::WallJump, c);
            return;
        }
        
        bool intentionIntoWall = c.Body().Walled.IsRight() ? c.Intent().MoveX > 0 : c.Intent().MoveX < 0;

        if ((intentionIntoWall && c.Intent().Down.Held) || (c.Intent().MoveX == 0 && !c.Intent().Down.Held))
        {
            Animation slideAnim = c.Body().Walled.IsRight() ? Animation::WallSlideRight : Animation::WallSlideLeft;
            c.Animator().Play(slideAnim);
            c.Movement().AccelY = -c.Stats().WallSlideGravity;
        }
        else if (intentionIntoWall)
        {
            Animation contactAnim = c.Body().Walled.IsRight() ? Animation::WallContactRight : Animation::WallContactLeft;
            c.Animator().Play(contactAnim);
            c.Movement().AccelY = 0;
            c.Body().Velocity.y = 0;
        }
        else if (c.Intent().Down.Held)
        {
            c.Body().Velocity.x = 50 * c.Body().Walled.IsRight() ? -1 : 1;
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::WallSlide;
    }
};
