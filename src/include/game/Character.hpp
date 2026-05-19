#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"

enum class CharacterState
{
    Idle,
    Walk,
    Run,
    JumpStart,
    JumpMid,
    JumpFall,
    Attack,
    Defend,
    Hurt,
};

class Character
{
public:
    Character(glm::vec2 position, glm::vec2 size);
    ~Character() = default;

    void Update(float dt, bool animationFinished);

    void Attack() { m_state = CharacterState::Attack; m_body.Position = glm::vec2(320.f, 360.f); m_body.Velocity *= 0.f; }
    void Jump();
    void Idle();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Defend();


    CharacterState GetState() const { return m_state; }

    KinematicBody& GetBody() { return m_body; }
    glm::vec2 GetPosition() const { return m_body.Position; }
    glm::vec2 GetSize() const { return m_size; }

    bool IsFacingRight() { return m_isFacingRight; }

protected:
    CharacterState m_state;

    KinematicBody m_body;

    glm::vec2 m_size;


    bool m_isFacingRight;

    int m_health;

    float m_defendCooldownTimer = 1.f;

private:

};