#pragma once

#include <memory>

#include "CharacterState.hpp"


class IStateFactory
{
public:
    virtual std::unique_ptr<CharacterState>
    Create(StateID id) = 0;
};
