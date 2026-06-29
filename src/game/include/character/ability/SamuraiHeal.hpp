#pragma once

#include "IAbility.hpp"


class SamuraiHeal : public IAbility
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
        std::cout << "Heal ability" << std::endl;

        m_isActive = true;

        if (c.Heals() > 0)
        {
            c.Animator().Play(Animation::Healing);
            m_healing = true;
        }
        else
        {
            std::cout << "No healing" << std::endl;
            c.Animator().Play(Animation::HealingNoEffect);
            m_healing = false;
        }
        
        c.StateMachine().RequestState(StateID::Attacking, c);

        c.Movement().TargetSpeedX = 0;
        c.Movement().AccelX = c.Stats().RunAccel;
        c.Movement().DeccelX = c.Stats().RunDeccel;
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            c.Defence() = 0.0f;
            return;
        }

        if (std::abs(c.Intent().MoveX) > 0 && c.Animator().IsAfterFrame(3))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }     

        if (c.Intent().Jump.Pressed && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (m_healing && !m_healed && c.Animator().IsAfterFrame(9))
        {
            c.Heals() -= 1;
            c.Health() += 80;
            c.Health() = std::max(c.Health(), c.Stats().MaxHealth);
            m_healed = true;
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.Defence() = 0.0f;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }
    }

private:
    bool m_healing = true;

    bool m_healed = false;

};
