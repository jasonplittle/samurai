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
    WallContactLeft,
    WallContactRight,
    WallJump,
    WallSlideLeft,
    WallSlideRight
};


struct AnimationClip
{
    int StartFrame = 0;
    int FrameCount = 0;
    float FrameDuration = 0.f;
    bool Loop = false;
    bool IsStill = false;
    bool FlipX = false;
    glm::vec2 FrameCenterOffset = glm::vec2(0, 0);
    glm::vec2 FrameSize;
    std::unique_ptr<Sprite> Sprite;
};


struct AnimationSet
{
    std::unordered_map<Animation, AnimationClip> Clips;
};


using AnimationMap = std::unordered_map<Animation, Animation>;


class AnimationSetPlayer
{
public:
    AnimationSetPlayer(Animation initState, AnimationSet animationSet, AnimationMap animationMap);

    void Update(float dt);
    void Play(Animation animation);

    int GetCurrentFrame() const { return m_currentFrame; }
    const Sprite& GetCurrentSprite() const { return *m_animationSet.Clips.at(m_currentAnimation).Sprite; }

    bool IsBeforeFrame(int frameNumber) { return m_currentFrame + 1 < frameNumber; }
    bool IsAfterFrame(int frameNumber) { return m_currentFrame + 1 >= frameNumber; } // Todo split frames. i.e compare to 1.5

    bool FlipX() const { return m_animationSet.Clips.at(m_currentAnimation).FlipX; }

    bool IsFinished() const { return m_isFinished; }

    glm::vec2 GetFrameSize() const { return m_animationSet.Clips.at(m_currentAnimation).FrameSize; }
    glm::vec2 GetFrameCenterOffset() const { return m_animationSet.Clips.at(m_currentAnimation).FrameCenterOffset; }

private:
    Animation m_currentAnimation;
    AnimationSet m_animationSet;
    AnimationMap m_animationMap;

    int m_currentFrame;
    float m_timeInCurrentFrame;

    bool m_isFinished;
};


class AnimationPlayer
{
public:
    AnimationPlayer();
    AnimationPlayer(AnimationClip& animationClip);
    void Update(float dt);

    const Sprite& GetCurrentSprite() const { return *m_animationClip.Sprite; }
    int GetCurrentFrame() const { return m_currentFrame; }

    glm::vec2 GetFrameSize() const { return m_animationClip.FrameSize; }
    glm::vec2 GetFrameCenterOffset() const { return m_animationClip.FrameCenterOffset; }

private:
    AnimationClip& m_animationClip;
    int m_currentFrame;
    float m_timeInCurrentFrame;

};
