#pragma once

#include "PhysicsSystem.hpp"
#include "SpriteRenderer.hpp"
#include "Projectile.hpp"


class ProjectileManager
{
public:
    void AddProjectile(std::unique_ptr<Projectile>& projectile)
    {
        m_projectiles.push_back(std::move(projectile));
    }

    void Update(float dt, PhysicsSystem& physics, const World& world)
    {
        for (auto& projectile : m_projectiles)
        {
            physics.UpdateBody(projectile->Body, world, dt);

            if (!projectile->Body.IsGrounded || projectile->Body.Walled.IsFree())
            {
                projectile->Hitbox->KeepHitboxAlive();
            }
            else
            {
                projectile->Body.Acceleration = glm::vec2(0, 0);
                projectile->Body.Velocity = glm::vec2(0, 0);
            }
        }
    }

    void DrawProjectiles(SpriteRenderer& renderer, OrthographicCamera& camera)
    {
        for (auto& projectile : m_projectiles)
        {
            Sprite* sprite;
            
            if (projectile->Type == ProjectileType::Shuriken)
                sprite = &*m_shurikenSprite;

            renderer.Render(
                *sprite,
                glm::ivec2(0, 0),
                false,
                camera,
                projectile->Body.Position,
                sprite->GetSize(),
                projectile->Body.IsGrounded || !projectile->Body.Walled.IsFree() ? 0.6 : 1.0 
            );
        }
    }

private:
    std::vector<std::unique_ptr<Projectile>> m_projectiles;
    std::unique_ptr<Sprite> m_shurikenSprite = std::make_unique<Sprite>("resources/samurai/shuriken.png", glm::vec2(8, 8));
};
