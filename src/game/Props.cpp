#include "Props.hpp"

#include <iostream>

Props::Props(PropSet propSet) : m_propSet(std::move(propSet))
{}


void Props::AddProp(int worldX, const World& world)
{
    Prop prop;

    if (worldX % 3 == 0)
        prop.Id = PropId::Tree1;
    else if (worldX % 2 == 1)
        prop.Id = PropId::Tree2;
    else
        prop.Id = PropId::Tree3;

    int worldY = world.WorldXToGroundY(worldX);

    prop.Position = glm::vec2(worldX, worldY);

    for (auto& prop : m_props)
    {
        if (prop.Position.x == worldX && prop.Position.y == worldY)
            return;
    }

    m_props.push_back(prop);
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
