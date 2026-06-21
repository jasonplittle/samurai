#pragma once

#include "CharacterState.hpp"
#include "AirBourne.hpp"

class WallJumpState : public CharacterState, public AirBourne
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall jump state" << std::endl;
        c.Animator().Play(Animation::WallJump);

        c.Body().Velocity.y = 0;
        c.Body().Velocity.x = c.Stats().JumpVelocity * 0.5 * (c.IsFacingRight() ? 1 : -1);
        c.Body().Velocity.y = c.Stats().JumpVelocity;
        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().DoubleJumpUsed = false;
    }

    void Update(Character& c, float dt) override
    {
        m_jumpTimer += dt;

        if (m_jumpTimer > k_wallControlTime)
        {
            bool exit = AirBourneUpdate(c, dt);
            if (exit) return;
        }
        else
        {
            c.Body().Acceleration.x = c.Movement().AccelX;
            c.Body().Acceleration.y = c.Movement().AccelY;
        }

        if (c.Stats().CanDoubleJump && c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed)
        {
            c.Movement().DoubleJumpUsed = true;
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Body().Walled != 0 && m_jumpTimer > k_wallReconnectTime)
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }

        if (c.Animator().IsFinished())
        {
            c.Movement().AccelX = c.Stats().RunAccel;
            c.Movement().DeccelX = c.Stats().RunDeccel;
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
    const float k_wallReconnectTime = 0.1f;
    const float k_wallControlTime = 0.1f;

};
