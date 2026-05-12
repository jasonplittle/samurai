#pragma once

#include <glm/glm.hpp>

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
    Character() : m_state(CharacterState::Idle), m_size(96, 96) {};
    ~Character() = default;

    void Update(float dt, bool animationFinished);

    void Attack() { m_state = CharacterState::Attack; }
    void Jump() { m_state = CharacterState::Jump; };
    void Idle() { m_state = CharacterState::Idle; };
    void MoveLeft() { m_state = CharacterState::Walk; m_isFacingRight = false; m_pos.x -= 1.f; };
    void MoveRight() { m_state = CharacterState::Walk; m_isFacingRight = true; m_pos.x += 1.f; };

    CharacterState GetState() const { return m_state; }

    glm::vec2 GetPosition() const { return m_pos; }
    glm::vec2 GetSize() const { return m_size; }

    bool IsFacingRight() { return m_isFacingRight; }

protected:
    CharacterState m_state;

    glm::vec2 m_pos = {0.f, 0.f};
    glm::vec2 m_vel;
    glm::vec2 m_size;

    bool m_grounded;
    bool m_attacking;
    bool m_isFacingRight;

    int m_health;

private:

};