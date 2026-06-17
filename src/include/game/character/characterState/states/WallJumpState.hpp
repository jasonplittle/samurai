#pragma once

#include "CharacterState.hpp"


class WallJumpState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall jump state" << std::endl;
        c.Animator().Play(Animation::WallJump);

        c.Body().Velocity.y = 0;
        c.Body().Velocity.x = c.Stats().JumpVelocity * (c.IsFacingRight() ? -1 : 1);
        std::cout << c.Body().Velocity.x << std::endl;
        c.Movement().AccelY = -c.Stats().WallSlideGravity;
    }

    void Update(Character& c, float dt) override
    {
        m_jumpTimer += dt;

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Intent().Down)
        {
            c.Movement().AccelY = -c.Stats().FastFallGravity;
            c.StateMachine().RequestState(StateID::Fall, c);
            return;
        }

        if (c.Body().IsWalled && m_jumpTimer > m_wallReconnectTime)
        {
            c.StateMachine().RequestState(StateID::WallSlide, c);
            return;
        }

        if (c.Animator().IsFinished())
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::WallJump;
    }


private:
    float m_jumpTimer = 0.0f;
    float m_wallReconnectTime = 0.2f;

};
