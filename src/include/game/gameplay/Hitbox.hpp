#pragma once

#include <glm/glm.hpp>
#include <unordered_set>

class Character;


struct Rect
{
    float Left;
    float Top;
    float Right;
    float Bottom;
};


static bool Intersects(const Rect& a, const Rect& b)
{
    return
        a.Left   < b.Right  &&
        a.Right  > b.Left   &&
        a.Top    < b.Bottom &&
        a.Bottom > b.Top;
}


class Hitbox
{
public:
    glm::vec2 PositionOffset;
    glm::vec2 Radii;

    float Damage;
    float Knockback;

    Character* Instigator;

    bool Canceled = false;
    bool KeepAlive = true;

    std::unordered_set<Character*> HitTargets;

    Rect Bounds() const;
    bool IsAlive() const;
    void Update(float dt);

    void KeepHitboxAlive() { KeepAlive = true; }
};
