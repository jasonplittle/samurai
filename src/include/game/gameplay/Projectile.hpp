#pragma once


#include "Hitbox.hpp"
#include "PhysicsSystem.hpp"


enum class ProjectileType
{
    Shuriken,
};

struct Projectile
{
    ProjectileType Type;
    KinematicBody Body;
    std::shared_ptr<Hitbox> Hitbox;
    glm::vec2 Size;
};
