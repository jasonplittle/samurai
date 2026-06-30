#pragma once

#include "IAbilityFactory.hpp"

#include "ExecutionerCleaveCombo.hpp"


class ExecutionerAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            case AbilitySlot::Primary:
                return std::make_unique<ExecutionerCleaveCombo>();

            case AbilitySlot::Secondary:
                return std::make_unique<ExecutionerCleaveCombo>();

            case AbilitySlot::Ultimate:
                return std::make_unique<ExecutionerCleaveCombo>();

            default:
                return nullptr;
        }
    }
};
