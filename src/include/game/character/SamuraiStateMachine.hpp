#pragma once


#include "ICharacterStateMachine.hpp"


class SamuraiStateMachine : public ICharacterStateMachine
{
public:
    SamuraiStateMachine() = delete;
    SamuraiStateMachine(CharacterState initState) : ICharacterStateMachine(initState) {}

    void Update(Character& character, float dt) override;

private:
    bool CanChange(CharacterState state, Character& character) override;
    void OnExit(CharacterState state) override;
    void OnEnter(CharacterState state) override;

private:
    float m_defendCooldownTimer = 1.f;
};
