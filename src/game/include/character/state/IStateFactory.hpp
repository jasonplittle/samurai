#pragma once

#include <memory>

#include "ICharacterState.hpp"


class IStateFactory
{
public:
    virtual std::unique_ptr<ICharacterState> Create(StateID id) = 0;
};
