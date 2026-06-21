#pragma once

#include "SpriteRenderer.hpp"
#include "World.hpp"


enum class PropId
{
    Tree1,
    Tree2,
    Tree3,
    Bush1,
    Bush2,
    Bush3,
    Bush4,
    Bush5,
    Bush6,
    Bush7,
    Lamp,
    Well,
    Torii,
    Flag,
};

enum class PropType
{
    Tree,
    Bush,
    Object,
};


struct Prop
{
    glm::vec2 Position;
    PropId Id;
    PropType Type;
};


struct PropInfo
{
    glm::vec2 Size;
    std::unique_ptr<Sprite> Sprite;
};


struct PropSet
{
    std::unordered_map<PropId, PropInfo> Set;
};


class Props
{
public:
    Props(PropSet propSet);

    void AddProp(int WorldX, const World& world);
    void DrawProps(SpriteRenderer& renderer, OrthographicCamera camera);

private:
    std::vector<Prop> m_props;
    PropSet m_propSet;
};
