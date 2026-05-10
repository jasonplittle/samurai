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
    CharacterAnimation(CharacterState initState, AnimationSet animationSet);

    void Update(float dt);

private:
    AnimationSet animationSet;
    CharacterState m_currentState;

};
