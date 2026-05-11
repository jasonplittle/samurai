#pragma once

#include <glm/glm.hpp>

enum class CharacterState
{
    Idle,
    Run,
    Jump,
    Attack,
    Hurt,
};

class Character
{
public:
    Character() : m_characterState(CharacterState::Idle), m_size(200, 200) {};
    ~Character() = default;

    // virtual void Attack() = 0;
    // virtual void Jump() = 0;

    void Attack() {};
    void Jump() {};

    CharacterState GetState() const { return m_characterState; }


    glm::vec2 GetPosition() const { return m_pos; }
    glm::vec2 GetSize() const { return m_size; }

    bool IsFacingRight() { return true; }

protected:
    CharacterState m_characterState;

    glm::vec2 m_pos;
    glm::vec2 m_vel;
    glm::vec2 m_size;

    bool m_grounded;
    bool m_attacking;

    int m_health;

private:

};