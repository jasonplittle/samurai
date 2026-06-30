#pragma once

#include "IAbility.hpp"
#include "Projectile.hpp"


class ArcherTripleShot : public IAbility
{
public:
    bool CanActivate(Character& c) const override
    {
        if (c.StateMachine().CheckState(StateID::Death))
            return false;

        return true;
    }

    virtual bool CanBeOverriden(Character& c) const override { return false; }

    void Activate(Character& c) override
    {
        std::cout << "Archer triple shot ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::SpecialAttack);
        c.StateMachine().RequestState(StateID::Attacking, c);

        c.Movement().TargetSpeedX = 10;

        c.SetInvincibility(true);
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            c.SetInvincibility(false);
            m_isActive = false;
            return;
        }

        if (c.Body().IsGrounded && c.Intent().Jump.Pressed && c.Animator().IsAfterFrame(2))
        {
            m_isActive = false;
            c.SetInvincibility(false);
            c.StateMachine().RequestState(StateID::Jump, c);
            return;
        }

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (!m_arrowSpawned1 && c.Animator().IsAfterFrame(11))
        {
            std::unique_ptr<Projectile> arrow = std::make_unique<Projectile>(Projectile
            {
                .Type = ProjectileType::Arrow,
                .Body = KinematicBody {
                    .Position = c.Body().Position + glm::vec2(32 * (c.IsFacingRight() ? 1 : -1), 14),
                    .Velocity = glm::vec2(500 * (c.IsFacingRight() ? 1 : -1), 0),
                    .Acceleration = glm::vec2(40 * (c.IsFacingRight() ? -1 : 1), -10),
                    .Radii = glm::vec2(8, 1),
                },
                .Hitbox = std::make_shared<Hitbox>(Hitbox
                {
                    .PositionOffset = glm::vec2(10, 0),
                    .Radii = glm::vec2(10, 4),
                    .Damage = 15.f,
                    .Knockback = 250.f,
                    .Instigator = &c,
                }),
                .Size = glm::vec2(4, 4)
            });

            arrow->Hitbox->Origin = &arrow->Body;

            c.GameplayContext().SpawnProjectile(arrow);

            m_arrowSpawned1 = true;

            c.SetInvincibility(false);
        }

        if (!m_arrowSpawned2 && c.Animator().IsAfterFrame(14))
        {
            std::unique_ptr<Projectile> arrow = std::make_unique<Projectile>(Projectile
            {
                .Type = ProjectileType::Arrow,
                .Body = KinematicBody {
                    .Position = c.Body().Position + glm::vec2(32 * (c.IsFacingRight() ? 1 : -1), -3),
                    .Velocity = glm::vec2(500 * (c.IsFacingRight() ? 1 : -1), 0),
                    .Acceleration = glm::vec2(40 * (c.IsFacingRight() ? -1 : 1), -10),
                    .Radii = glm::vec2(8, 1),
                },
                .Hitbox = std::make_shared<Hitbox>(Hitbox
                {
                    .PositionOffset = glm::vec2(10, 0),
                    .Radii = glm::vec2(10, 4),
                    .Damage = 15.f,
                    .Knockback = 250.f,
                    .Instigator = &c,
                }),
                .Size = glm::vec2(4, 4)
            });

            arrow->Hitbox->Origin = &arrow->Body;

            c.GameplayContext().SpawnProjectile(arrow);

            m_arrowSpawned2 = true;
        }

        if (!m_arrowSpawned3 && c.Animator().IsAfterFrame(17))
        {
            std::unique_ptr<Projectile> arrow = std::make_unique<Projectile>(Projectile
            {
                .Type = ProjectileType::Arrow,
                .Body = KinematicBody {
                    .Position = c.Body().Position + glm::vec2(32 * (c.IsFacingRight() ? 1 : -1), 4),
                    .Velocity = glm::vec2(500 * (c.IsFacingRight() ? 1 : -1), 0),
                    .Acceleration = glm::vec2(40 * (c.IsFacingRight() ? -1 : 1), -10),
                    .Radii = glm::vec2(8, 1),
                },
                .Hitbox = std::make_shared<Hitbox>(Hitbox
                {
                    .PositionOffset = glm::vec2(10, 0),
                    .Radii = glm::vec2(10, 4),
                    .Damage = 15.f,
                    .Knockback = 250.f,
                    .Instigator = &c,
                }),
                .Size = glm::vec2(4, 4)
            });

            arrow->Hitbox->Origin = &arrow->Body;

            c.GameplayContext().SpawnProjectile(arrow);

            m_arrowSpawned3 = true;
        }
    }

private:
    bool m_arrowSpawned1 = false;
    bool m_arrowSpawned2 = false;
    bool m_arrowSpawned3 = false;

    float m_minMoveVal;
};
