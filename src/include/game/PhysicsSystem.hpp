#pragma once

#include <glm/glm.hpp>

struct Rigidbody
{
    glm::vec2 velocity = {0.0f, 0.0f};

    glm::vec2 forces = {0.f, 0.0f};

    float mass = 1.0f;

    bool useGravity = true;

    bool grounded = false;
};

struct Transform
{
    glm::vec2 position;
};

struct BoxCollider
{
    glm::vec2 halfSize;
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
        if (rigidbody.useGravity)
        {
            rigidbody.forces.y -=
                gravity * rigidbody.mass;
        }

        // Acceleration
        glm::vec2 acceleration =
            rigidbody.forces / rigidbody.mass;

        // Integrate Velocity
        rigidbody.velocity +=
            acceleration * dt;

        // Integrate Position
        transform.position +=
            rigidbody.velocity * dt;

        // Clear Forces
        rigidbody.forces = {0.0f, 0.0f};
    }

    bool Collides(
        const Transform& aTransform,
        const BoxCollider& aCollider,
        const Transform& bTransform,
        const BoxCollider& bCollider)
    {
        return
            std::abs(aTransform.position.x -
                    bTransform.position.x)
                < (aCollider.halfSize.x +
                bCollider.halfSize.x)

            &&

            std::abs(aTransform.position.y -
                    bTransform.position.y)
                < (aCollider.halfSize.y +
                bCollider.halfSize.y);
    }

private:
    float gravity = 30.0f;
};