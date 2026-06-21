#pragma once

#include "Character.hpp"
#include "IStateFactory.hpp"

class Character;


class CharacterStateMachine
{
public:
    CharacterStateMachine(std::unique_ptr<IStateFactory> stateFactory) : m_stateFactory(std::move(stateFactory)) {};

    void Update(Character& c, float dt)
    {
        if (m_current)
        {
            m_current->Update(c, dt);
        }
    }

    bool RequestState(StateID next, Character& c)
    {
        if (!m_current)
        {
            bool changed = ChangeState(next, c);
            return changed;
        }

        if (m_current->GetID() == next)
        {
            return true;
        }

        if (!m_current->CanTransitionTo(next, c))
        {
            return false;
        }

        bool changed = ChangeState(next, c);

        return changed;
    }

    bool CheckState(StateID state)
    {
        return state == m_current->GetID();
    }

private:
    bool ChangeState(StateID next, Character& c)
    {
        if (m_current)
        {
            m_current->Exit(c);
        }

        m_current = m_stateFactory->Create(next); // Check if null ptr return false;

        if (!m_current) return false;

        m_current->Enter(c);

        return true;
    }

private:
    std::unique_ptr<CharacterState> m_current;
    std::unique_ptr<IStateFactory> m_stateFactory;
};
