#pragma once

#include <memory>

#include "CharacterState.hpp"


enum class StateID
{
    Idle,
    Walk,
    Run,
    Jump,
    Fall,
    SwordCombo,
};


class IStateFactory
{
public:
    virtual std::unique_ptr<CharacterState>
    Create(StateID id) = 0;
};
