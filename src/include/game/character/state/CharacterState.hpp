#pragma once

#include <iostream>

#include "CharacterStateMachine.hpp"


class Character;


enum class StateID
{
    Idle,
    Walk,
    Run,
    Jump,
    Float,
    Fall,
    Attacking,
    Hurt,
    Death,
    WallSlide,
    WallJump,
    Dash
};


class CharacterState
{
public:
    virtual ~CharacterState() = default;

    virtual void Enter(Character& c) {}
    virtual void Exit(Character& c) {}

    virtual void Update(Character& c, float dt) = 0;

    virtual bool CanTransitionTo(StateID next, Character& c)
    {
        return true;
    }

    virtual StateID GetID() const = 0;
};