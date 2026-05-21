#pragma once

#include "CharacterState.hpp"

class WalkState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Walk state" << std::endl;
        c.Animator().Play(Animation::Walk);

        c.Movement().TargetSpeedX = c.Stats().RunSpeed;
        c.Movement().AccelX = c.Stats().WalkAccel;
        c.Movement().DeccelX = c.Stats().WalkDeccel;
    }

    void Update(Character& c, float dt) override
    {
        m_walkTimer += dt;

        float speed = std::abs(c.Body().Velocity.x);

        if (!c.Body().IsGrounded)
        {
            c.StateMachine().RequestState(StateID::Fall, c);
            return;
        }

        if (speed >= c.Stats().WalkSpeed && m_walkTimer >= k_walkTimeReq)
        {
            c.StateMachine().RequestState(StateID::Run, c);
            return;
        }

        if (speed < c.Stats().IdleSpeed)
        {
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

    StateID GetID() const override
    {
        return StateID::Walk;
    }

private:
    float m_walkTimer = 0;
    const float k_walkTimeReq = 0.5;
};