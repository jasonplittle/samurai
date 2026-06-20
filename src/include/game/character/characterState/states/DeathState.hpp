#pragma once

#include "CharacterState.hpp"


class DeathState : public CharacterState
{
public:
    void Enter(Character& c) override
    {
        std::cout << "Death state" << std::endl;
        c.Animator().Play(Animation::Death);

        c.Movement().AccelY = -c.Stats().Gravity;
        c.Movement().DeccelX = c.Stats().RunDeccel;
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

        if (m_dead && c.DeathDecay() > 0.5)
            c.DeathDecay() -= dt;
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
};