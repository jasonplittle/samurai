#pragma once

#include <memory>

#include "IAbility.hpp"

enum class AbilitySlot
{
    Primary,
    Secondary,
    Movement,
};


class IAbilityFactory
{
public:
    virtual std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) = 0;
};
