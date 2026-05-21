#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"
#include "CharacterStateMachine.hpp"
#include "ChacterStats.hpp"



enum class ActionState
{
    None,
    Attacking,
    Defending,
    Hurt,
    Dead
};

enum class MovementState
{
    Idle,
    Walk,
    Run,
    Jump,
    Fall,
    Float
};


class Character
{
public:
    Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine);
    ~Character() = default;

    void Update(float dt, bool animationFinished);

    void AbilityPrimary();
    void AbilitySecondary();
    void MoveUp();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Idle();


    CharacterState GetState() const { return m_stateMachine.GetCurrentState(); }

    KinematicBody& GetBody() { return m_body; }
    glm::vec2 GetPosition() const { return m_body.Position; }
    glm::vec2 GetSize() const { return glm::vec2(m_stats.Width, m_stats.Height); }

    bool IsFacingRight() { return m_isFacingRight; }

private:
    KinematicBody m_body;
    CharacterStats m_stats;
    ICharacterStateMachine m_stateMachine;

    bool m_isFacingRight;
    int m_health;
};