#pragma once

#include <glm/glm.hpp>

#include "PhysicsSystem.hpp"
#include "CharacterStateMachine.hpp"
#include "CharacterAnimator.hpp"
#include "CharacterAbilities.hpp"
#include "IGameplayContext.hpp"
#include "Hitbox.hpp"


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
    InputButton Primary;
    InputButton Secondary;
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
};


struct CharacterStats
{
    int MaxHealth;
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

    bool CanRun = false;
};


class Character
{
public:
    Character(glm::vec2 initPosition, CharacterStats stats, CharacterStateMachine stateMachine, CharacterAnimator animator, CharacterAbilities abilities, IGameplayContext& gameplayContext);

    void Update(float dt, std::vector<Hitbox>& hitboxes);

    void SetIntent(CharacterIntent intent) { m_currentIntent = intent; };

    KinematicBody& Body() { return m_body; }
    CharacterAnimator& Animator() { return m_animator; }
    CharacterStateMachine& StateMachine() { return m_stateMachine; }
    CharacterStats& Stats() { return m_stats; }
    MovementProfile& Movement() { return m_movementProfile; }
    CharacterIntent& Intent() { return m_currentIntent; }
    IGameplayContext& GameplayContext() { return m_gameplayContext; }
    Rect Hurtbox() const;

    bool& IsFacingRight() { return m_isFacingRight; }
    void Motor();

    float Health() { return m_health; }
    bool IsAlive() { return m_health >= 0.0; }
    float& DeathDecay() { return m_deathDecay; }

private:
    bool applyHitboxes(std::vector<Hitbox>& hitboxes);

private:
    KinematicBody m_body;
    CharacterStats m_stats;
    CharacterStateMachine m_stateMachine;
    CharacterAnimator m_animator;

    CharacterIntent m_currentIntent;
    MovementProfile m_movementProfile;
    
    CharacterAbilities m_abilities;

    IGameplayContext& m_gameplayContext;

    bool m_isFacingRight;
    float m_health;
    bool m_isAlive = true;
    float m_deathDecay = 1.0;
};
