#pragma once

#include "Hitbox.hpp"


class IGameplayContext
{
public:
    virtual ~IGameplayContext() = default;

    virtual void SpawnHitbox(std::shared_ptr<Hitbox> htibox) = 0;

    // virtual void SpawnProjectile(const ProjectileDesc&) = 0;
};
