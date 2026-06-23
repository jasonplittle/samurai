#pragma once

#include "ICharacterState.hpp"


class WallJumpState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall jump state" << std::endl;

        float velx = c.Stats().JumpVelocity;
        float vely = c.Stats().JumpVelocity;
        bool intentionIntoWall = c.Body().Walled.IsRight() ? c.Intent().MoveX > 0 : c.Intent().MoveX < 0;

        if (intentionIntoWall || c.Intent().MoveX == 0)
        {
            c.Animator().Play(Animation::Jump);
            velx *= 0.5f * (c.Body().Walled.IsRight() ? -1 : 1);
            vely *= 0.7f;
        }
        else
        {
            c.Animator().Play(Animation::WallJump);
            velx *= 0.7f * (c.Body().Walled.IsRight() ? -1 : 1);
            vely *= 0.5f;
        }

        c.Body().Velocity.x = velx;
        c.Body().Velocity.y = vely;
        
        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        m_jumpTimer += dt;

        if (m_jumpTimer >= k_wallControlTime)
        {
            c.Motor();
        }

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Stats().CanDoubleJump && c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed)
        {
            c.StateMachine().RequestState(StateID::DoubleJump, c);
            return;
        }

        if (c.Stats().CanWallSlide && c.Body().Walled.IsFull())
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }

        if (c.Animator().IsFinished())
        {
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::WallJump;
    }


private:
    float m_jumpTimer = 0.0f;
    const float k_wallControlTime = 0.1f;

};
