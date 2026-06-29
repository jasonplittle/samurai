#pragma once

#include "IAbility.hpp"


class SamuraiGroundDash : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

        if (!c.Body().IsGrounded)
            return false;

        return true;
    }

    void Activate(Character& c) override
    {
        std::cout << "Ground dash ability" << std::endl;

        m_isActive = true;

        c.StateMachine().RequestState(StateID::Dash, c);
        c.Animator().Play(Animation::Dash);

        c.Body().Velocity.x = 200 * (c.IsFacingRight() ? 1 : -1);
        c.Body().Acceleration.x = 0;
        c.Body().Acceleration.y = -c.Stats().FloatGravity;

        c.SetInvincibility(true);
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Dash))
        {
            m_isActive = false;
            c.SetInvincibility(false);
            return;
        }

        if (c.Intent().Jump.Pressed && c.Body().IsGrounded)
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (c.Intent().Jump.Pressed && !c.Body().IsGrounded && !c.Movement().DoubleJumpUsed)
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::DoubleJump, c);
            return;
        }

        if (c.Animator().IsAfterFrame(5))
        {
            c.SetInvincibility(false);
            c.Motor();

            if (!c.Body().IsGrounded)
            {
                c.StateMachine().RequestState(StateID::Float, c);
                return;
            }

            if (std::abs(c.Intent().MoveX) > 0)
            {
                m_isActive = false;
                c.StateMachine().RequestState(StateID::Run, c);
                return;
            }
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

};
