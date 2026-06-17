#pragma once

#include "CharacterState.hpp"


class WallSlideState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Wall slide state" << std::endl;
        c.Animator().Play(Animation::WallContact);

        c.Body().Velocity.y = 0;
        c.Movement().AccelY = -c.Stats().WallSlideGravity;
    }

    void Update(Character& c, float dt) override
    {
        m_slideTimer += dt;

        if (c.Body().Velocity.y < m_fastSlideThresh && !m_fastSlide)
        {
            m_fastSlide = true;
            c.Animator().Play(Animation::WallSlide);
        }

        if (c.Body().Velocity.y >= m_fastSlideThresh && m_fastSlide)
        {
            m_fastSlide = false;
            c.Animator().Play(Animation::WallContact);
        }

        if (c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Intent().Down)
        {
            c.Movement().AccelY = -c.Stats().FastFallGravity;
            return;
        }

        if (c.Intent().Jump && m_slideTimer > m_wallJumpTime)
        {
            c.StateMachine().RequestState(StateID::WallJump, c);
            return;
        }

        if (!c.Body().IsWalled && m_slideTimer > m_wallFallTime)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::WallSlide;
    }

private:
    bool m_fastSlide = false;
    float m_fastSlideThresh = -100.f;

    float m_slideTimer = 0.0f;
    float m_wallJumpTime = 0.2f;
    float m_wallFallTime = 0.3f;

};
