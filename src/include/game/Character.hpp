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
    Character(glm::vec2 position, glm::vec2 size);
    ~Character() = default;

    void Update(float dt, bool animationFinished);

    void Attack() { m_state = CharacterState::Attack; }
    void Jump() { m_state = CharacterState::Jump; m_body.Position = glm::vec2(100.f, 0.f); };
    void Idle() { m_state = CharacterState::Idle; m_body.Acceleration.x = 0; };
    void MoveLeft() { m_state = CharacterState::Walk; m_isFacingRight = false; m_body.Acceleration.x = -100; };
    void MoveRight() { m_state = CharacterState::Walk; m_isFacingRight = true; m_body.Acceleration.x = 100; };
    void MoveDown() { m_state = CharacterState::Walk; };


    CharacterState GetState() const { return m_state; }

    KinematicBody& GetBody() { return m_body; }
    glm::vec2 GetPosition() const { return m_body.Position; }
    glm::vec2 GetSize() const { return m_size; }

    bool IsFacingRight() { return m_isFacingRight; }

protected:
    CharacterState m_state;

    KinematicBody m_body;

    glm::vec2 m_size;

    float m_targetSpeed = 0;
    float m_acc = 10;

    bool m_grounded;
    bool m_attacking;
    bool m_isFacingRight;

    int m_health;

private:

};