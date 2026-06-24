#pragma once

#include <memory>

#include "IAbility.hpp"


enum class AbilitySlot
{
    Primary,
    AirPrimary,
    Secondary,
    Dash,
    Down,
    Defend,
    Ultimate,
    Heal,
};


class IAbilityFactory
{
public:
    virtual std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) = 0;
};
