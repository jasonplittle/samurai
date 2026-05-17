#pragma once

#include <glm/glm.hpp>

constexpr float GRAVITY = 30.f;

struct Rigidbody
{
    glm::vec2 Velocity = glm::vec2(0.f, 0.f);
    glm::vec2 Acceleration = glm::vec2(0.f, 0.f);
    float Mass = 1.0f;
    bool UseGravity = false;
    bool Grounded = true;
};

struct Transform
{
    glm::vec2 Position = glm::vec2(0.f, 0.f);
};

struct BoxCollider
{
    glm::vec2 Size;
    glm::vec2 HalfSize;
};


class PhysicsSystem
{
public:
    void Update(
        Transform& transform,
        Rigidbody& rigidbody,
        float dt)
    {
        // Gravity
        if (rigidbody.UseGravity)
        {
            rigidbody.Acceleration.y += gravity * dt;
        }

        // Integrate Velocity
        rigidbody.Velocity += rigidbody.Acceleration * dt;

        // Integrate Position
        transform.Position += rigidbody.Velocity * dt;
    }

    bool Collides(
        const Transform& aTransform,
        const BoxCollider& aCollider,
        const Transform& bTransform,
        const BoxCollider& bCollider)
    {
        return
            std::abs(aTransform.Position.x -
                    bTransform.Position.x)
                < (aCollider.HalfSize.x +
                bCollider.HalfSize.x)

            &&

            std::abs(aTransform.Position.y -
                    bTransform.Position.y)
                < (aCollider.HalfSize.y +
                bCollider.HalfSize.y);
    }

private:
    float gravity = 30.0f;
    float friction = 20.f;
};