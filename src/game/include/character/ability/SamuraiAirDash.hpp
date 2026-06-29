#pragma once

#include "IAbility.hpp"


class SamuraiAirDash : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

        if (c.Body().IsGrounded)
            return false;

        return true;
    }

    void Activate(Character& c) override
    {
        std::cout << "Air dash ability" << std::endl;

        m_isActive = true;

        c.StateMachine().RequestState(StateID::Dash, c);
        c.Animator().Play(Animation::Dash);

        c.Body().Velocity.x = 200 * (c.IsFacingRight() ? 1 : -1);
        c.Body().Velocity.y = c.Stats().JumpVelocity * 0.3f;
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

        if (c.Body().IsGrounded)
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::Run, c);
            return;
        }

        if (c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed)
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::DoubleJump, c);
            return;
        }

        if (c.Animator().IsAfterFrame(5))
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::Float, c);
            return;
        }
        else if (c.Animator().IsAfterFrame(1))
        {
            c.Body().Velocity.x = 350 * (c.IsFacingRight() ? 1 : -1);
        }
    }

};
