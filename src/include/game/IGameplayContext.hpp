#pragma once

#include "Hitbox.hpp"


class IGameplayContext
{
public:
    virtual ~IGameplayContext() = default;

    virtual void SpawnHitbox(const Hitbox&) = 0;

    // virtual void SpawnProjectile(const ProjectileDesc&) = 0;
};
