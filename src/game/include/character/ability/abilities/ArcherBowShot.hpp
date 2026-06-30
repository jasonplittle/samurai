#pragma once

#include "IAbility.hpp"
#include "Projectile.hpp"


class ArcherBowShot : public IAbility
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
        std::cout << "Bow shot ability" << std::endl;

        m_isActive = true;
        c.Animator().Play(Animation::Attack1);
        c.StateMachine().RequestState(StateID::Attacking, c);

        c.Movement().TargetSpeedX = 20;
        m_minMoveVal = std::abs(c.Intent().MoveX);
    }

    void Update(Character& c, float dt) override
    {
        if (!c.StateMachine().CheckState(StateID::Attacking))
        {
            m_isActive = false;
            return;
        }

        if (std::abs(c.Intent().MoveX) < m_minMoveVal)
        {
            m_minMoveVal = std::abs(c.Intent().MoveX);
        }

        if (std::abs(c.Intent().MoveX) > m_minMoveVal + 0.2f)
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

        if (c.Animator().IsFinished())
        {
            m_isActive = false;
            c.StateMachine().RequestState(StateID::Idle, c);
            return;
        }

        if (!m_arrowSpawned && c.Animator().IsAfterFrame(6))
        {
            std::unique_ptr<Projectile> arrow = std::make_unique<Projectile>(Projectile
            {
                .Type = ProjectileType::Arrow,
                .Body = KinematicBody {
                    .Position = c.Body().Position + glm::vec2(32 * (c.IsFacingRight() ? 1 : -1), 7),
                    .Velocity = glm::vec2(400 * (c.IsFacingRight() ? 1 : -1), 0),
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

            m_arrowSpawned = true;
        }
    }

private:
    bool m_arrowSpawned = false;

    float m_minMoveVal;
};
