#pragma once

#include "Character.hpp"


enum class CharacterState
{
    Idle,
    Walk,
    Run,
    JumpStart,
    JumpMid,
    JumpFall,
    WallContact,
    WallSlide,
    Attack1,
    Attack2,
    Attack3,
    Defend,
    Hurt,
};


class ICharacterStateMachine
{
public:
    ICharacterStateMachine(CharacterState initState) : m_state(initState) {};

    CharacterState GetCurrentState() { return m_state; }

    bool RequestState(CharacterState newState, Character& character)
    {
        if (m_state == newState)
            return true;

        if (!CanChange(newState, character))
            return false;

        OnExit(m_state);

        m_state = newState;

        OnEnter(m_state);

        return true;
    }

    virtual void Update(Character& character, float dt) = 0;

protected:
    virtual bool CanChange(CharacterState state, Character& character) = 0;
    virtual void OnExit(CharacterState state) = 0;
    virtual void OnEnter(CharacterState state) = 0;

    CharacterState m_state;
};
