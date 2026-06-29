#pragma once

#include "IAbility.hpp"
#include "Projectile.hpp"


class SamuraiShuriken : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

        return true;
    }

    void Activate(Character& c) override
    {
        std::cout << "Shuriken ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::Throw);
        c.StateMachine().RequestState(StateID::Attacking, c);

        c.Movement().AccelY = -c.Stats().FallGravity;
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (std::abs(c.Intent().MoveX) > 0 && c.Animator().IsAfterFrame(3))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (c.Body().IsGrounded && c.Intent().Jump.Pressed && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (!c.Body().IsGrounded && c.Intent().Jump.Pressed && !c.Movement().DoubleJumpUsed && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::DoubleJump, c);
            return;
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (!m_shurikenSpawned && c.Animator().IsAfterFrame(4))
        {
            std::unique_ptr<Projectile> shuriken = std::make_unique<Projectile>(Projectile
            {
                .Type = ProjectileType::Shuriken,
                .Body = KinematicBody {
                    .Position = c.Body().Position + glm::vec2(32 * (c.IsFacingRight() ? 1 : -1), 0),
                    .Velocity = glm::vec2(300 * (c.IsFacingRight() ? 1 : -1), 0),
                    .Acceleration = glm::vec2(40 * (c.IsFacingRight() ? -1 : 1), -10),
                    .Radii = glm::vec2(1, 1),
                },
                .Hitbox = std::make_shared<Hitbox>(Hitbox
                {
                    .PositionOffset = glm::vec2(0, 0),
                    .Radii = glm::vec2(4, 4),
                    .Damage = 15.f,
                    .Knockback = 250.f,
                    .Instigator = &c,
                }),
                .Size = glm::vec2(4, 4)
            });

            shuriken->Hitbox->Origin = &shuriken->Body;

            c.GameplayContext().SpawnProjectile(shuriken);

            m_shurikenSpawned = true;
        }
    }

private:
    bool m_shurikenSpawned = false;
};
