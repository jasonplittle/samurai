#pragma once

#include <memory>
#include <iostream>

#include "Hitbox.hpp"
#include "SpriteRenderer.hpp"


class HitboxManager
{
public:
    const std::vector<std::shared_ptr<Hitbox>>& GetHitboxes() const { return m_hitboxes; }

    void AddHitbox(std::shared_ptr<Hitbox> hitbox)
    {
        m_hitboxes.push_back(hitbox);
    }

    void Update(float dt)
    {
        std::cout << "Hit length: " << m_hitboxes.size() << std::endl;

        for (auto it = m_hitboxes.begin(); it != m_hitboxes.end(); )
        {
            if (!(*it)->IsAlive())
            {
                it = m_hitboxes.erase(it);
            }
            else
            {
                (*it)->Update(dt);
                ++it;
            }
        }
    }

    void DrawHitboxes(SpriteRenderer& renderer, OrthographicCamera camera)
    {
        for (auto& hitbox : m_hitboxes)
        {
            renderer.Render(
                *m_sprite,
                glm::ivec2(0, 0),
                false,
                camera,
                glm::vec2((hitbox->Bounds().Left + hitbox->Bounds().Right) / 2, (hitbox->Bounds().Bottom + hitbox->Bounds().Top) / 2),
                glm::vec2(hitbox->Bounds().Right - hitbox->Bounds().Left, hitbox->Bounds().Bottom - hitbox->Bounds().Top),
                0.5
            );
        }
    }

private:
    std::vector<std::shared_ptr<Hitbox>> m_hitboxes;
    std::unique_ptr<Sprite> m_sprite = std::make_unique<Sprite>("resources/props/BlackSquare.png", glm::vec2(32, 32));
};
