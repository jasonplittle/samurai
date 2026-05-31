#pragma once

#include "IAbility.hpp"


class SamuraiSlashCombo : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (!c.Body().IsGrounded)
            return false;

        // if (c.IsStunned())
        //     return false;

        return true;
    }

    void Activate(Character& c) override
    {
        if (m_attackPhase == 0)
        {
            m_isActive = true;
            c.Animator().Play(Animation::Attack1);
            c.StateMachine().RequestState(StateID::Attacking, c);
            m_attackPhase = 1;
        }

        if (m_attackPhase == 1 && m_timeInPhase > 0.6)
        {
            m_attackPhase = 2;
            m_timeInPhase = 0.f;
            m_nextPhaseRequesed = true;
        }

        if (m_attackPhase == 2 && m_timeInPhase > 0.6)
        {
            m_attackPhase = 3;
            m_timeInPhase = 0.f;
            m_nextPhaseRequesed = true;
        }

        // SpawnHitbox(c);
    }

    void Update(Character& c, float dt) override
    {
        m_timeInPhase += dt;

        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (c.Animator().IsFinished())
        {
            if (!m_nextPhaseRequesed)
            {
                m_isActive = false;
                c.StateMachine().RequestState(StateID::Idle, c);
                return;
            }

            if (m_attackPhase == 2)
            {
                c.Animator().Play(Animation::Attack2);
                m_timeInPhase = 0.f;
                m_nextPhaseRequesed = false;
            }

            if (m_attackPhase == 3)
            {
                c.Animator().Play(Animation::Attack3);
                m_timeInPhase = 0.f;
                m_nextPhaseRequesed = false;
            }
        }        
    }

private:
    int m_attackPhase = 0;
    float m_timeInPhase = 0.0f;
    bool m_nextPhaseRequesed = false;

    // Move stats
};
