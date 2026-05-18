#pragma once

#include <glm/glm.hpp>

#include "World.hpp"

#include <iostream>


constexpr float GRAVITY = 30.f;


struct KinematicBody
{
    bool UseGravity = false;
    bool IsGrounded = false;
    bool IsSolid = false;

    glm::vec2 Position = glm::vec2(0.f, 0.f);
    glm::vec2 Velocity = glm::vec2(0.f, 0.f);
    glm::vec2 Acceleration = glm::vec2(0.f, 0.f);

    glm::vec2 Radii = glm::vec2(0.f, 0.f);
};


class PhysicsSystem
{
public:
    void UpdateBody(KinematicBody& body, World& world, float dt)
    {
        if (body.UseGravity)
        {
            body.Acceleration.y = -GRAVITY;
        }

        body.Velocity += body.Acceleration * dt;


        // Move and collide

        body.Position.x += body.Velocity.x * dt;

        int bodyTop = body.Position.y + body.Radii.y;
        int bodyBottom = body.Position.y - body.Radii.y;
        int bodyLeft = body.Position.x - body.Radii.x;
        int bodyRight = body.Position.x + body.Radii.x;

        for (int y = bodyBottom; y <= bodyTop; y++)
        {
            if (world.IsSolid(bodyLeft, y))
            {
                body.Position.x = world.WorldXToTileRightX(bodyLeft) + body.Radii.x;
                body.Velocity.x = 0;
                break;
            }

            if (world.IsSolid(bodyRight, y))
            {
                body.Position.x = world.WorldXToTileLeftX(bodyRight) - body.Radii.x;
                body.Velocity.x = 0;
                break;
            }
        }

        body.Position.y += body.Velocity.y * dt;

        bodyTop = body.Position.y + body.Radii.y;
        bodyBottom = body.Position.y - body.Radii.y;
        bodyLeft = body.Position.x - body.Radii.x;
        bodyRight = body.Position.x + body.Radii.x;

        for (int x = bodyLeft; x <= bodyRight; x++)
        {
            if (world.IsSolid(x, bodyTop))
            {
                body.Position.y += world.WorldYToTileBottomY(bodyTop) - body.Radii.y;
                body.Velocity.y = 0;
                break;
            }

            if (world.IsSolid(x, bodyBottom))
            {
                body.Position.y = world.WorldYToTileTopY(bodyBottom) + body.Radii.y;
                body.Velocity.y = 0;
                body.IsGrounded = true;
                break;
            }
        }
    }
};