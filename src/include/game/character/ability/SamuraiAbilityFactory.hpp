#pragma once

#include "IAbilityFactory.hpp"

#include "SamuraiSlashCombo.hpp"


class SamuraiAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            case AbilitySlot::Primary:
                return std::make_unique<SamuraiSlashComboAbility>();

            default:
                return nullptr;
        }
    }
};
