#pragma once

#include <glm/glm.hpp>

#include "World.hpp"

#include <iostream>


enum class WalledState
{
    Free,
    PartialLeft,
    FullLeft,
    PartialRight,
    FullRight,
};

struct Walled
{
    WalledState State = WalledState::Free;

    bool IsFree() const { return State == WalledState::Free; }
    bool IsPartial() const { return State == WalledState::PartialLeft || State == WalledState::PartialRight; }
    bool IsFull() const { return State == WalledState::FullLeft || State == WalledState::FullRight; }

    bool IsLeft() const { return State == WalledState::PartialLeft || State == WalledState::FullLeft; }
    bool IsRight() const { return State == WalledState::PartialRight || State == WalledState::FullRight; }
};


struct KinematicBody
{
    bool IsGrounded = false;
    Walled Walled = { .State = WalledState::Free };
    bool IsSolid = false;

    glm::vec2 Position = glm::vec2(0.f, 0.f);
    glm::vec2 Velocity = glm::vec2(0.f, 0.f);
    glm::vec2 Acceleration = glm::vec2(0.f, 0.f);

    glm::vec2 Radii = glm::vec2(0.f, 0.f);
};


class PhysicsSystem
{
public:
    void UpdateBody(KinematicBody& body, const World& world, float dt)
    {
        body.IsGrounded = false;
        body.Walled.State = WalledState::Free;
        body.Velocity += body.Acceleration * dt;

        body.Position.y += body.Velocity.y * dt;
        CollideY(body, world);

        body.Position.x += body.Velocity.x * dt;
        DetectWalls(body, world);
        CollideX(body, world);        
    }

    void DetectWalls(KinematicBody& body, const World& world)
    {
        int bodyTop    = body.Position.y + body.Radii.y + 8;
        int bodyBottom = body.Position.y - body.Radii.y;
        int bodyLeft   = body.Position.x - body.Radii.x;
        int bodyRight  = body.Position.x + body.Radii.x;

        // std::cout << bodyTop << ", " << bodyBottom << std::endl;

        int sampleCount = 0;

        int leftHits = 0;
        int rightHits = 0;

        for (int y = bodyBottom; y <= bodyTop; ++y)
        {
            ++sampleCount;

            if (world.IsSolid(bodyLeft, y))
                ++leftHits;

            if (world.IsSolid(bodyRight, y))
                ++rightHits;
        }

        if (leftHits > 0)
        {
            body.Walled.State = (leftHits == sampleCount) ? WalledState::FullLeft : WalledState::PartialLeft;
        }

        if (rightHits > 0)
        {
            body.Walled.State = (rightHits == sampleCount) ? WalledState::FullRight : WalledState::PartialRight;
        }
    }

    bool CollideX(KinematicBody& body, const World& world)
    {
        int bodyTop = body.Position.y + body.Radii.y;
        int bodyBottom = body.Position.y - body.Radii.y;
        int bodyLeft = body.Position.x - body.Radii.x;
        int bodyRight = body.Position.x + body.Radii.x;

        for (int y = bodyBottom; y < bodyTop; y++)
        {
            if (world.IsSolid(bodyLeft, y))
            {
                body.Position.x = world.WorldXToTileRightX(bodyLeft) + body.Radii.x;
                body.Velocity.x = 0;
                return true;
            }

            if (world.IsSolid(bodyRight, y))
            {
                body.Position.x = world.WorldXToTileLeftX(bodyRight) - body.Radii.x;
                body.Velocity.x = 0;
                return true;
            }
        }
        return false;
    }

    bool CollideY(KinematicBody& body, const World& world)
    {
        int bodyTop = body.Position.y + body.Radii.y;
        int bodyBottom = body.Position.y - body.Radii.y;
        int bodyLeft = body.Position.x - body.Radii.x;
        int bodyRight = body.Position.x + body.Radii.x;

        for (int x = bodyLeft; x < bodyRight; x++)
        {
            if (world.IsSolid(x, bodyBottom))
            {
                body.Position.y = world.WorldYToTileTopY(bodyBottom) + body.Radii.y;
                body.Velocity.y = 0;
                body.IsGrounded = true;
                return true;
            }

            if (world.IsSolid(x, bodyTop))
            {
                body.Position.y = world.WorldYToTileBottomY(bodyTop) - body.Radii.y;
                body.Velocity.y = 0;
                return true;
            }
        }
        return false;
    }

};