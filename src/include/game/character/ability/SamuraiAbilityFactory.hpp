#pragma once

#include "IAbilityFactory.hpp"

#include "SamuraiSlashCombo.hpp"
#include "SamuraiAirAttack.hpp"


class SamuraiAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            case AbilitySlot::Primary:
                return std::make_unique<SamuraiSlashCombo>();

            case AbilitySlot::AirPrimary:
                return std::make_unique<SamuraiAirAttack>();

            default:
                return nullptr;
        }
    }
};
