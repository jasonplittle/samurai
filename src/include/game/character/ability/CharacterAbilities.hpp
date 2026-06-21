#pragma once

#include <optional>
#include <queue>

#include "Character.hpp"
#include "IAbilityFactory.hpp"

class Character;


class CharacterAbilities
{
public:
    CharacterAbilities(std::unique_ptr<IAbilityFactory> abilityFactory) : m_abilityFactory(std::move(abilityFactory)) {}

    void Update(Character& c, float dt)
    {
        if (!m_requests.empty())
        {
            for (auto& reqSlot : m_requests)
            {
                if (m_activeSlot.has_value() && reqSlot == m_activeSlot.value())
                {
                    m_current->Trigger(c);
                    break;
                }

                std::unique_ptr<IAbility> nextAbility = m_abilityFactory->CreateAbility(reqSlot);

                if (!nextAbility)
                    continue;

                if (!nextAbility->CanActivate(c))
                    continue;

                if (m_current)
                    m_current->Cancel(c);

                m_current = std::move(nextAbility);
                m_current->Activate(c);
                m_activeSlot.emplace(reqSlot);
                break;
            }
            m_requests.clear();
        }

        if (!m_current)
            return;

        if (m_current->IsFinished())
        {
            m_activeSlot.reset();
            return;
        }

        m_current->Update(c, dt);
    }

    void RequestAbility(Character& c, AbilitySlot slot)
    {
        m_requests.push_back(slot);
        return;
    }

    void CancelAbility(Character& c)
    {
        if (m_current)
        {
            m_current->Cancel(c);
            m_activeSlot.reset();
        }
    }

private:
    std::optional<AbilitySlot> m_activeSlot;
    std::vector<AbilitySlot> m_requests;
    std::unique_ptr<IAbility> m_current;
    std::unique_ptr<IAbilityFactory> m_abilityFactory;
};
