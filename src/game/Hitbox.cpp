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



// std::unique_ptr<Sprite> spr = std::make_unique<Sprite>("resources/world/Tileset.png", glm::vec2(32, 32));

    // for (auto& hitbox : m_hitboxes)
    // {
    //     m_renderer.Render(
    //         *spr,
    //         glm::ivec2(1, 4), 
    //         false,
    //         m_camera,
    //         glm::vec2((hitbox.Bounds().Left + hitbox.Bounds().Right) / 2, (hitbox.Bounds().Bottom + hitbox.Bounds().Top) / 2),
    //         glm::vec2(hitbox.Bounds().Right - hitbox.Bounds().Left, hitbox.Bounds().Bottom - hitbox.Bounds().Top)
    //     );
    // }

    // m_renderer.Render(
    //     *spr,
    //     glm::ivec2(1, 4), 
    //     false,
    //     m_camera,
    //     glm::vec2((m_player2->Hurtbox().Left + m_player2->Hurtbox().Right) / 2, (m_player2->Hurtbox().Bottom + m_player2->Hurtbox().Top) / 2),
    //     glm::vec2(m_player2->Hurtbox().Right - m_player2->Hurtbox().Left, m_player2->Hurtbox().Bottom - m_player2->Hurtbox().Top)
    // );

    // m_renderer.Render(
    //     *spr,
    //     glm::ivec2(1, 4), 
    //     false,
    //     m_camera,
    //     glm::vec2((m_player1->Hurtbox().Left + m_player1->Hurtbox().Right) / 2, (m_player1->Hurtbox().Bottom + m_player1->Hurtbox().Top) / 2),
    //     glm::vec2(m_player1->Hurtbox().Right - m_player1->Hurtbox().Left, m_player1->Hurtbox().Bottom - m_player1->Hurtbox().Top)
    // );