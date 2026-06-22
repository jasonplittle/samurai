#pragma once

#include "ICharacterState.hpp"


class WallSlideState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall state" << std::endl;

        if (c.Body().Walled == 1)
        {
            c.Animator().Play(Animation::WallContactRight);
            c.IsFacingRight() = false;
            c.Movement().AccelX = 1;
        }
        else if (c.Body().Walled == -1)
        {
            c.Animator().Play(Animation::WallContactLeft);
            c.IsFacingRight() = true;
            c.Movement().AccelX = -1;
        }

        c.Body().Velocity.y = 0;
        c.Movement().AccelY = -c.Stats().WallSlideGravity;
        c.Movement().DeccelX = c.Stats().RunDeccel;

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

        if (c.Body().Walled == 1)
        {
            if (c.Intent().MoveX > 0)
            {
                c.Animator().Play(Animation::WallContactRight);
                c.Movement().AccelY = 0;
                c.Body().Velocity.y = 0;
            }
            else if (c.Intent().MoveX == 0)
            {
                c.Animator().Play(Animation::WallSlideRight);
                c.Movement().AccelY = -c.Stats().WallSlideGravity;
            }
            else if (c.Intent().MoveX < 0)
            {
                c.Movement().AccelX = c.Stats().RunAccel;
                
                c.Movement().TargetSpeedX = c.Stats().RunSpeed;
                c.Body().Velocity.x = -50;
                c.StateMachine().RequestState(StateID::Float, c);
                return;
            }
        }

        if (c.Body().Walled == -1)
        {
            if (c.Intent().MoveX < 0)
            {
                c.Animator().Play(Animation::WallContactLeft);
                c.Movement().AccelY = 0;
                c.Body().Velocity.y = 0;
            }
            else if (c.Intent().MoveX == 0)
            {
                c.Animator().Play(Animation::WallSlideLeft);
                c.Movement().AccelY = -c.Stats().WallSlideGravity;
            }
            else if (c.Intent().MoveX > 0)
            {
                c.Movement().AccelX = c.Stats().RunAccel;
                c.Movement().TargetSpeedX = c.Stats().RunSpeed;
                c.Body().Velocity.x = 50;
                c.StateMachine().RequestState(StateID::Float, c);
                return;
            }
        }        
    }

    StateID GetID() const override
    {
        return StateID::WallSlide;
    }
};
