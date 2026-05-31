#pragma once

#include "Character.hpp"


class Character;

class IAbility
{
public:
    virtual ~IAbility() = default;

    virtual bool CanActivate(Character& c) const = 0;

    virtual void Activate(Character& c) = 0;

    virtual void Update(Character& c, float dt) {}

    virtual void Cancel(Character& c) { m_isActive = false; }

    virtual bool IsFinished() const
    {
        return !m_isActive;
    }

protected:
    bool m_isActive = true;

};