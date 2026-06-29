#pragma once

#include "SpriteRenderer.hpp"
#include "World.hpp"
#include "Animator.hpp"


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
    std::unique_ptr<AnimationPlayer> Animator;
};


struct PropInfo
{
    glm::vec2 Size;
    AnimationClip AnimationClip;
};


struct PropSet
{
    std::unordered_map<PropId, PropInfo> Set;
};


class Props
{
public:
    Props(std::unique_ptr<PropSet> propSet);

    void AddProp(int WorldX, const World& world);
    void Update(float dt);
    void DrawProps(SpriteRenderer& renderer, OrthographicCamera camera);

private:
    std::vector<Prop> m_props;
    std::unique_ptr<PropSet> m_propSet;
};
