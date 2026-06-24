#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"
#include "CharacterStateMachine.hpp"
#include "Animator.hpp"
#include "CharacterAbilities.hpp"
#include "IGameplayContext.hpp"
#include "Hitbox.hpp"
#include "HitboxManager.hpp"


struct InputButton
{
    bool Pressed = false;
    bool Released = false;
    bool Held = false;
};

struct CharacterIntent
{
    float MoveX = 0.f;

    InputButton Jump;
    InputButton Down;
    InputButton Slow;
    InputButton Defend;
    InputButton Primary;
    InputButton Secondary;
    InputButton Ultimate;
    InputButton Heal;
    bool Dash = false;
};


struct MovementProfile
{
    float TargetSpeedX;

    float AccelX;
    float DeccelX;

    float AccelY;
    float DeccelY;

    bool DoubleJumpUsed = true;
    bool DashUsed = true;
};


struct CharacterStats
{
    float MaxHealth;
    int Mass;

    bool CanJump;
    bool CanDoubleJump = false;
    float JumpVelocity;
    float Gravity;
    float FloatGravity;
    float FallGravity;
    float FastFallGravity;

    float Width;
    float Height;
    float RadiusX;
    float RadiusY;

    float IdleSpeed;
    float WalkSpeed;
    float RunSpeed;

    float WalkAccel;
    float WalkDeccel;

    float RunAccel;
    float RunDeccel;

    bool CanWallSlide;
    float WallSlideGravity;

    float PrimaryAttackRange;

    int MaxHeals = 0;

    bool CanRun = false;
};


class Character
{
public:
    Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, AnimationSetPlayer animator, CharacterAbilities abilities, IGameplayContext& gameplayContext);

    void Update(float dt, const HitboxManager& hitboxManager);

    void SetIntent(CharacterIntent intent) { m_currentIntent = intent; };

    KinematicBody& Body() { return m_body; }
    AnimationSetPlayer& Animator() { return m_animator; }
    CharacterStateMachine& StateMachine() { return m_stateMachine; }
    CharacterStats& Stats() { return m_stats; }
    MovementProfile& Movement() { return m_movementProfile; }
    CharacterIntent& Intent() { return m_currentIntent; }
    IGameplayContext& GameplayContext() { return m_gameplayContext; }
    Rect Hurtbox() const;

    bool& IsFacingRight() { return m_isFacingRight; }
    void Motor();

    float& Health() { return m_health; }
    int& Heals() { return m_heals; }
    float& Defence() { return m_defence; }
    bool IsAlive() { return m_health >= 0.0; }
    float& DeathDecay() { return m_deathDecay; }

private:
    bool applyHitboxes(const HitboxManager& hitboxManager);

private:
    KinematicBody m_body;
    CharacterStats m_stats;
    CharacterStateMachine m_stateMachine;
    AnimationSetPlayer m_animator;

    CharacterIntent m_currentIntent;
    MovementProfile m_movementProfile;
    
    CharacterAbilities m_abilities;

    IGameplayContext& m_gameplayContext;

    bool m_isFacingRight = true;
    float m_health;
    float m_defence = 0.0;
    bool m_isAlive = true;
    float m_deathDecay = 1.0;
    int m_heals = 0;
};
