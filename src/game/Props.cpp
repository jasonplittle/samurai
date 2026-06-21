#include "Props.hpp"
#include "Hitbox.hpp"

#include <iostream>


Props::Props(PropSet propSet) : m_propSet(std::move(propSet)) {}


void Props::AddProp(int worldX, const World& world)
{
    Prop newProp;

    switch (worldX % 24)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            newProp.Id = PropId::Tree1;
            newProp.Type = PropType::Tree;
            break;

        case 5:
        case 6:
        case 7:
        case 8:
            newProp.Id = PropId::Tree2;
            newProp.Type = PropType::Tree;
            break;

        case 9:
        case 10:
        case 11:
        case 12:
            newProp.Id = PropId::Tree3;
            newProp.Type = PropType::Tree;
            break;

        case 13:
            newProp.Id = PropId::Bush1;
            newProp.Type = PropType::Bush;
            break;

        case 14:
            newProp.Id = PropId::Bush2;
            newProp.Type = PropType::Bush;
            break;

        case 15:
            newProp.Id = PropId::Bush3;
            newProp.Type = PropType::Bush;
            break;

        case 16:
            newProp.Id = PropId::Bush4;
            newProp.Type = PropType::Bush;
            break;

        case 17:
            newProp.Id = PropId::Bush5;
            newProp.Type = PropType::Bush;
            break;
        
        case 18:
            newProp.Id = PropId::Bush6;
            newProp.Type = PropType::Bush;
            break;

        case 19:
            newProp.Id = PropId::Bush7;
            newProp.Type = PropType::Bush;
            break;

        case 20:
            newProp.Id = PropId::Lamp;
            newProp.Type = PropType::Object;
            break;

        case 21:
            newProp.Id = PropId::Torii;
            newProp.Type = PropType::Object;
            break;

        case 22:
            newProp.Id = PropId::Well;
            newProp.Type = PropType::Object;
            break;

        case 23:
            newProp.Id = PropId::Flag;
            newProp.Type = PropType::Object;
            break;
    }   

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

        if (Intersects(rec1, rec2) && (prop.Type == newProp.Type || (prop.Type != PropType::Bush && newProp.Type != PropType::Bush)))
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
