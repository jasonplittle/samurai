#pragma once

#include "ICharacterState.hpp"


class DeathState : public ICharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Death state" << std::endl;
        c.Animator().Play(Animation::Death);

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().DeccelX = 30;
    }

    void Update(Character& c, float dt) override
    {
        const float speedDif = -c.Body().Velocity.x;
        c.Body().Acceleration.x = speedDif * c.Movement().DeccelX;
        c.Body().Acceleration.y = c.Movement().AccelY;
        
        if (!m_dead && c.Animator().IsFinished())
        {
            c.Animator().Play(Animation::Dead);
            m_dead = true;
        }

        if (m_dead && !m_fullDead)
        {
            c.DeathDecay() -= dt;
            if (c.DeathDecay() <= 0.5)
            {
                m_fullDead = true;
                c.IsFullDead() = true;
            }
        }
    }

    virtual bool CanTransitionTo(StateID next, Character& c)
    {
        return false;
    }

    StateID GetID() const override
    {
        return StateID::Death;
    }

private:
    bool m_dead = false;
    bool m_fullDead = false;
};
