#include "Hitbox.hpp"
#include "Character.hpp"


Rect Hitbox::Bounds() const
{
    glm::vec2 center;

    if (Origin)
    {
        center = Origin->Position;
    }
    else
    {
        center = Instigator->Body().Position;
    }

    if (Instigator->IsFacingRight())
        center.x += PositionOffset.x;
    else
        center.x -= PositionOffset.x;

    center.y += PositionOffset.y;

    return Rect
    {
        center.x - Radii.x,
        center.y - Radii.y,
        center.x + Radii.x,
        center.y + Radii.y
    };
}


void Hitbox::Update(float dt)
{
    KeepAlive = false;
}

bool Hitbox::IsAlive() const
{
    if (!Instigator)
        return false;

    if (!Instigator->IsAlive())
        return false;

    return KeepAlive;
}
