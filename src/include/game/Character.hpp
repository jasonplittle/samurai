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
    Character() = default;
    ~Character() = default;

    virtual void Attack() = 0;
    virtual void Jump() = 0;

protected:
    CharacterState m_characterState;

    glm::vec2 m_pos;
    glm::vec2 m_vel;

    bool m_grounded;
    bool m_attacking;

    int m_health;

private:

};