#pragma once

#include "IAbility.hpp"


class SamuraiDash : public IAbility
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
        std::cout << "Dash ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::Dash);
        c.StateMachine().RequestState(StateID::Dash, c);
        
        c.IsFacingRight() = c.Intent().MoveX > 0;
        c.Movement().TargetSpeedX = c.Stats().RunSpeed * c.Intent().MoveX;
        c.Body().Velocity.x = 200 * c.Intent().MoveX;
        c.Movement().DeccelX = c.Stats().RunDeccel;
        c.Movement().AccelY = 0;
    }

    void Update(Character& c, float dt) override
    {
        const float speedDif = c.Movement().TargetSpeedX - c.Body().Velocity.x;
        c.Body().Acceleration.x = speedDif * c.Movement().DeccelX;
        c.Body().Acceleration.y = c.Movement().AccelY;

        if (!c.StateMachine().CheckState(StateID::Dash))
        {
            m_isActive = false;
            return;
        }

        if(c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Run, c);
            return;
        }
    }

};
