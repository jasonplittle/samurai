#pragma once

#include "IAbilityFactory.hpp"




class ArcherAbilityFactory : public IAbilityFactory
{
public:
    std::unique_ptr<IAbility> CreateAbility(AbilitySlot slot) override
    {
        switch (slot)
        {
            // case AbilitySlot::Primary:
            //     return std::make_unique<SamuraiSlashCombo>();

            // case AbilitySlot::AirPrimary:
            //     return std::make_unique<SamuraiAirAttack>();

            // case AbilitySlot::Down:
            //     return std::make_unique<SamuraiDive>();

            // case AbilitySlot::Dash:
            //     return std::make_unique<SamuraiDash>();

            // case AbilitySlot::Defend:
            //     return std::make_unique<SamuraiDefend>();

            // case AbilitySlot::Secondary:
            //     return std::make_unique<SamuraiShuriken>();

            // case AbilitySlot::Ultimate:
            //     return std::make_unique<SamuraiSlicingSlam>();

            // case AbilitySlot::Heal:
            //     return std::make_unique<SamuraiHeal>();

            default:
                return nullptr;
        }
    }
};
