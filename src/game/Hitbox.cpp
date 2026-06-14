#include "Hitbox.hpp"
#include "Character.hpp"


Rect Hitbox::Bounds() const
{
    glm::vec2 center = Instigator->Body().Position;

    if (Instigator->IsFacingRight())
        center += PositionOffset;
    else
        center -= PositionOffset;

    return Rect
    {
        center.x - Radii.x,
        center.y - Radii.y,
        center.x + Radii.x,
        center.y + Radii.y
    };
}
