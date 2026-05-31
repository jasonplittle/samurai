#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"
#include "CharacterStateMachine.hpp"
#include "CharacterAnimator.hpp"
#include "CharacterAbilities.hpp"


struct CharacterIntent
{
    bool Jump, Down, Primary, Secondary;
    int MoveX;
};

struct MovementProfile
{
    float TargetSpeedX;

    float AccelX;
    float DeccelX;

    float AccelY;
    float DeccelY;
};

struct CharacterStats
{
    int MaxHealth;

    float JumpVelocity;
    float Gravity;
    float FallGravity;
    float FastFallGravity;

    float Width;
    float Height;

    float IdleSpeed;
    float WalkSpeed;
    float RunSpeed;

    float WalkAccel;
    float WalkDeccel;

    float RunAccel;
    float RunDeccel;
};


class Character
{
public:
    Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator, CharacterAbilities abilities);

    void Update(float dt);

    void SetIntent(CharacterIntent intent) { m_currentIntent = intent; };

    KinematicBody& Body() { return m_body; }
    CharacterAnimator& Animator() { return m_animator; }
    CharacterStateMachine& StateMachine() { return m_stateMachine; }
    CharacterStats& Stats() { return m_stats; }
    MovementProfile& Movement() { return m_movementProfile; }
    CharacterIntent& Intent() { return m_currentIntent; }

    bool IsFacingRight() { return m_isFacingRight; }

private:
    KinematicBody m_body;
    CharacterStats m_stats;
    CharacterStateMachine m_stateMachine;
    CharacterAnimator m_animator;

    CharacterIntent m_currentIntent;
    MovementProfile m_movementProfile;
    
    CharacterAbilities m_abilities;

    bool m_isFacingRight;
    int m_health;
};
