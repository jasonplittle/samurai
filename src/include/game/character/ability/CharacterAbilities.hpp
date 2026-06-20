#pragma once

#include <optional>

#include "Character.hpp"
#include "IAbilityFactory.hpp"

class Character;


class CharacterAbilities
{
public:
    CharacterAbilities(std::unique_ptr<IAbilityFactory> abilityFactory) : m_abilityFactory(std::move(abilityFactory)) {}

    void Update(Character& c, float dt)
    {
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
        if (m_activeSlot.has_value() && slot == m_activeSlot.value())
        {
            m_current->Trigger(c);
            return;
        }

        m_next = m_abilityFactory->CreateAbility(slot);
        if (!m_next || !m_next->CanActivate(c))
            return;

        if (m_current)
            m_current->Cancel(c);

        m_current = std::move(m_next);
        m_next = nullptr;
        m_current->Activate(c);
        m_activeSlot.emplace(slot);
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
    std::unique_ptr<IAbility> m_current;
    std::unique_ptr<IAbility> m_next;
    std::unique_ptr<IAbilityFactory> m_abilityFactory;
};
