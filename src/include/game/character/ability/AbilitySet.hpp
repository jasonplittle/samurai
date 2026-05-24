#pragma once

#include "IAbility.hpp"
#include "Character.hpp"


class Character;

enum class AbilitySlot
{
    Primary,
    Secondary,
    Movement,
};


class AbilitySet
{
public:
    void AddAbility(AbilitySlot slot, std::unique_ptr<IAbility> ability)
    {
        m_abilities.emplace_back(slot, std::move(ability));
    }

    void ActivateSlot(AbilitySlot slot, Character& c)
    {
        for (int i = 0; i < m_abilities.size(); i++)
        {
            if (m_abilities[i].first != slot)
                continue;

            if (m_abilities[i].second->CanActivate(c))
            {
                m_abilities[i].second->Activate(c);
                m_activeAbility = i;
                return;
            }
        }
    }

    void Update(Character& c, float dt)
    {
        if (m_activeAbility != -1)
            m_abilities.at(m_activeAbility).second->Update(c, dt);
    }

private:
    std::vector<std::pair<AbilitySlot, std::unique_ptr<IAbility>>> m_abilities;
    int m_activeAbility = -1;
};
