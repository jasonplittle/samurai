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

    virtual void Cancel(Character& c) {}

    virtual bool IsFinished() const
    {
        return true;
    }
};