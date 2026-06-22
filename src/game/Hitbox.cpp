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


void Hitbox::Update(float dt)
{
    if (UseRealTime)
    {
        TimeAlive += dt;
    }
}

bool Hitbox::IsAlive() const
{
    if (Canceled)
        return false;

    if (!Instigator)
        return false;

    if (!Instigator->IsAlive())
        return false;

    if (UseRealTime)
        return TimeAlive < Lifetime;

    return Instigator->Animator().GetCurrentFrame() < StartFrame + LifetimeFrames;
}
