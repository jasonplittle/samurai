#include "IAbility.hpp"


class SamuraiSlashComboAbility : public IAbility
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
        c.StateMachine().RequestState(StateID::Attacking, c);
        c.Animator().Play(Animation::Attack1);


        // SpawnHitbox(c);
    }

    void Update(Character& c, float dt) override
    {
        m_activatedDelta += dt;
        if (c.Animator().IsFinished())
        {
            if (c.Intent().Primary)
            {
                c.Animator().Play(Animation::Attack3);
            }
            else
            {
                c.StateMachine().RequestState(StateID::Idle, c);
            }
        }

    }

private:
    float m_activatedDelta = 0.0f;
    int m_attackPhase = 0;

    // Move stats

};
