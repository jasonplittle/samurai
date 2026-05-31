#pragma once

#include "IAbilityFactory.hpp"

#include "SamuraiSlashCombo.hpp"


class ExecutionerAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            default:
                return nullptr;
        }
    }
};
