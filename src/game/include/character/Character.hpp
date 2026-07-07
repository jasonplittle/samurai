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

    InputButton Jump = { false, false, false };
    InputButton Down = { false, false, false };
    InputButton Defend = { false, false, false };
    InputButton Primary = { false, false, false };
    InputButton Secondary = { false, false, false };
    InputButton Throw = { false, false, false };
    InputButton Ultimate = { false, false, false };
    InputButton Heal = { false, false, false };
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
    float MaxStamina = 100.f;
    float MaxMana = 100.f;
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
    float StationaryAttackRange;

    int MaxHeals = 0;
    int MaxThrowables = 0;

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
    float& Stamina() { return m_stamina; }
    float& Mana() { return m_mana; }
    int& Heals() { return m_heals; }
    int& Throwables() { return m_throwables; }
    float& Defence() { return m_defence; }
    bool IsAlive() { return m_health > 0.0; }
    float& DeathDecay() { return m_deathDecay; }
    bool& IsFullDead() { return m_isFullDead; }


    bool CanDoubleJump() { return true; }

    void SetInvincibility(bool invincibility ) { m_isInvincable = invincibility; }

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
    float m_stamina;
    float m_mana;
    float m_defence = 0.0;
    bool m_isFullDead = false;
    float m_deathDecay = 1.0;
    int m_heals = 0;
    int m_throwables = 0;
    bool m_isInvincable = false;
};
