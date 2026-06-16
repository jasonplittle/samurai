#include "Props.hpp"
#include "Hitbox.hpp"

#include <iostream>


Props::Props(PropSet propSet) : m_propSet(std::move(propSet)) {}


void Props::AddProp(int worldX, const World& world)
{
    Prop newProp;

    if (worldX % 3 == 0)
        newProp.Id = PropId::Tree1;
    else if (worldX % 2 == 1)
        newProp.Id = PropId::Tree2;
    else
        newProp.Id = PropId::Tree3;

    int worldY = world.WorldXToGroundY(worldX);

    newProp.Position = glm::vec2(worldX, worldY);

    for (auto& prop : m_props)
    {
        Rect rec1 =
        {
            .Left = prop.Position.x - (m_propSet.Set[prop.Id].Size.x / 2),
            .Top = prop.Position.y,
            .Right = prop.Position.x + (m_propSet.Set[prop.Id].Size.x / 2),
            .Bottom = prop.Position.y + (m_propSet.Set[prop.Id].Size.y)
        };

        Rect rec2 =
        {
            .Left = newProp.Position.x - (m_propSet.Set[newProp.Id].Size.x / 2),
            .Top = newProp.Position.y,
            .Right = newProp.Position.x + (m_propSet.Set[newProp.Id].Size.x / 2),
            .Bottom = newProp.Position.y + (m_propSet.Set[newProp.Id].Size.y),
        };

        if (Intersects(rec1, rec2))
            return;
    }

    m_props.push_back(newProp);
}


void Props::DrawProps(SpriteRenderer& renderer, OrthographicCamera camera)
{
    for (auto& prop : m_props)
    {
        renderer.Render(
            *m_propSet.Set[prop.Id].Sprite,
            glm::ivec2(0, 0),
            false,
            camera,
            prop.Position + glm::vec2(0, (m_propSet.Set[prop.Id].Size.y / 2) - 2),
            m_propSet.Set[prop.Id].Size
        );
    }
}
