#pragma once

#include <unordered_map>

#include "Sprite.hpp"


enum class Animation
{
    AirAttack,
    Attack1,
    Attack2,
    Attack3,
    Climbing,
    Dash,
    Death,
    Dead,
    Defend,
    HealingNoEffect,
    Healing,
    Hurt,
    Idle,
    Fall,
    Jump,
    Float,
    Run,
    SpecialAttack,
    Throw,
    Walk,
    WallContact,
    WallJump,
    WallSlide
};

struct AnimationClip
{
    int StartFrame;
    int FrameCount;
    float FrameDuration;
    bool Loop;
    bool FlipX;
    std::unique_ptr<Sprite> Sprite;
};

struct AnimationSet
{
    std::unordered_map<Animation, AnimationClip> Clips;
    glm::vec2 FrameSize;
    glm::vec2 FrameCenterOffset;
};

using AnimationMap = std::unordered_map<Animation, Animation>;


class CharacterAnimator
{
public:
    CharacterAnimator(Animation initState, AnimationSet animationSet, AnimationMap animationMap);

    void Update(float dt);
    void Play(Animation animation);

    int GetCurrentFrame() const { return m_currentFrame; }
    const Sprite& GetCurrentSprite() const { return *m_animationSet.Clips.at(m_currentAnimation).Sprite; }

    bool FlipX() const { return m_animationSet.Clips.at(m_currentAnimation).FlipX; }

    bool IsFinished() const { return m_isFinished; }

    glm::vec2 GetFrameSize() const { return m_animationSet.FrameSize; }
    glm::vec2 GetFrameCenterOffset() const { return m_animationSet.FrameCenterOffset; }

private:
    Animation m_currentAnimation;
    AnimationSet m_animationSet;
    AnimationMap m_animationMap;

    int m_currentFrame;
    float m_timeInCurrentFrame;

    bool m_isFinished;
};
