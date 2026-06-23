#pragma once

#include "Hitbox.hpp"
#include "Projectile.hpp"


class IGameplayContext
{
public:
    virtual ~IGameplayContext() = default;

    virtual void SpawnHitbox(std::shared_ptr<Hitbox> htibox) = 0;

    virtual void SpawnProjectile(std::unique_ptr<Projectile>& projectile) = 0;
};
