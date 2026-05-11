#pragma once

#include <unordered_map>

#include "Sprite.hpp"
#include "Character.hpp"


struct AnimationClip
{
    int StartFrame;
    int FrameCount;
    float FrameDuration;
    bool Loop;
    std::unique_ptr<Sprite> Sprite;
};

struct AnimationSet
{
    std::unordered_map<CharacterState, AnimationClip> Clips;
};

class CharacterAnimation
{
public:
    CharacterAnimation(CharacterState initState, AnimationSet animationSet) : m_currentState(initState), m_animationSet(animationSet) {};
    void Update(float dt, CharacterState characterState);

private:
    CharacterState m_currentState;
    AnimationSet m_animationSet;
    int m_currentFrame;
};
