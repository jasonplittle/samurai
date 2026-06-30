#pragma once

#include "IAbilityFactory.hpp"
#include "ArcherBowShot.hpp"
#include "ArcherBlock.hpp"
#include "ArcherTripleShot.hpp"


class ArcherAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            case AbilitySlot::Primary:
                return std::make_unique<ArcherBowShot>();

            case AbilitySlot::Defend:
                return std::make_unique<ArcherBlock>();

            case AbilitySlot::Secondary:
                return std::make_unique<ArcherBowShot>();

            case AbilitySlot::Ultimate:
                return std::make_unique<ArcherTripleShot>();

            default:
                return nullptr;
        }
    }
};
