#pragma once

#include <glm/glm.hpp>

#include "World.hpp"


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
            body.Acceleration.y = GRAVITY;
        }

        body.Velocity += body.Acceleration * dt;

        body.Position.x += body.Velocity.x * dt;

        int top = body.Position.y - body.Radii.y;
        int bottom = body.Position.y + body.Radii.y;
        int left = body.Position.x - body.Radii.x;
        int right = body.Position.x + body.Radii.x;

        for (int y = bottom; y <= top; y++)
        {
            if (world.IsSolid(right, y))
            {
                body.Position.x -= body.Radii.x; // Temp
                body.Velocity.x = 0;
                break;
            }

            if (world.IsSolid(left, y))
            {
                body.Position.x += body.Radii.x; // Temp
                body.Velocity.x = 0;
                break;
            }
        }

        body.Position.y += body.Velocity.y * dt;

        top = body.Position.y - body.Radii.y;
        bottom = body.Position.y + body.Radii.y;
        left = body.Position.x - body.Radii.x;
        right = body.Position.x + body.Radii.x;

        for (int x = left; x <= right; x++)
        {
            if (world.IsSolid(x, top))
            {
                body.Position.y += body.Radii.y; // Temp
                body.Velocity.y = 0;
                break;
            }

            if (world.IsSolid(x, bottom))
            {
                body.Position.y -= body.Radii.y; // Temp
                body.Velocity.y = 0;
                body.IsGrounded = true;
                break;
            }
        }
    }
};