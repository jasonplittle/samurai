#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"

enum class CharacterState
{
    Idle,
    Walk,
    Run,
    Jump,
    Attack,
    Hurt,
};

class Character
{
public:
    Character(glm::vec2 position, glm::vec2 size, float mass);
    ~Character() = default;

    void Update(float dt, bool animationFinished);

    void Attack() { m_state = CharacterState::Attack; }
    void Jump() { m_state = CharacterState::Jump; m_transform.Position.y -= 1;};
    void Idle() { m_state = CharacterState::Idle; m_targetSpeed = 0; };
    void MoveLeft() { m_state = CharacterState::Walk; m_isFacingRight = false; m_targetSpeed = -100; };
    void MoveRight() { m_state = CharacterState::Walk; m_isFacingRight = true; m_targetSpeed = 100; };
    void MoveDown() { m_state = CharacterState::Walk; m_transform.Position.y += 1; };


    CharacterState GetState() const { return m_state; }

    glm::vec2 GetPosition() const { return m_transform.Position; }
    glm::vec2 GetSize() const { return m_collider.Size; }

    // Transform& GetTransform() { return m_transform; }
    // Rigidbody& GetRigidBody() { return m_body; }

    bool IsFacingRight() { return m_isFacingRight; }

protected:
    CharacterState m_state;

    Rigidbody m_rigidbody;
    BoxCollider m_collider;
    Transform m_transform;

    float m_targetSpeed = 0;
    float m_acc = 10;

    bool m_grounded;
    bool m_attacking;
    bool m_isFacingRight;

    int m_health;

private:

};