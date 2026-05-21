#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"
#include "CharacterStateMachine.hpp"
#include "CharacterStats.hpp"
#include "CharacterAnimator.hpp"


class Character
{
public:
    Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator);

    void Update(float dt);

    void AbilityPrimary();
    void AbilitySecondary();
    void MoveUp();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void Idle();

    KinematicBody& Body() { return m_body; }
    CharacterAnimator& Animator() { return m_animator; }
    CharacterStateMachine& StateMachine() { return m_stateMachine; }
    CharacterStats& Stats() { return m_stats; }

    bool IsFacingRight() { return m_isFacingRight; }

private:
    KinematicBody m_body;
    CharacterStats m_stats;
    CharacterStateMachine m_stateMachine;
    CharacterAnimator m_animator;

    bool m_isFacingRight;
    int m_health;
};