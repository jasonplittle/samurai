#include "Animator.hpp"

#include <iostream>


AnimationSetPlayer::AnimationSetPlayer(Animation initAnimation, AnimationSet animationSet, AnimationMap animationMap) 
    : m_currentAnimation(initAnimation), 
      m_animationSet(std::move(animationSet)),
      m_animationMap(animationMap)
{
    m_currentFrame = m_animationSet.Clips.at(m_currentAnimation).StartFrame;
}

void AnimationSetPlayer::Play(Animation animation)
{
    Animation nextAnimation = animation;

    if (auto it = m_animationMap.find(animation); it != m_animationMap.end())
    {
        nextAnimation = it->second;
    }

    if (nextAnimation != m_currentAnimation)
    {
        m_currentFrame = m_animationSet.Clips.at(nextAnimation).StartFrame;
        m_isFinished = false;
        m_timeInCurrentFrame = 0.f;
        m_currentAnimation = nextAnimation;
    }
}

void AnimationSetPlayer::Update(float dt)
{
    m_timeInCurrentFrame += dt;

    if (m_timeInCurrentFrame <= m_animationSet.Clips.at(m_currentAnimation).FrameDuration)
        return;

    m_currentFrame++;

    if (m_currentFrame >= m_animationSet.Clips.at(m_currentAnimation).FrameCount - m_animationSet.Clips.at(m_currentAnimation).StartFrame)
    {
        if (m_animationSet.Clips.at(m_currentAnimation).Loop)
        {
            m_currentFrame = m_animationSet.Clips.at(m_currentAnimation).StartFrame;
        }
        
        m_isFinished = true;
    }

    m_timeInCurrentFrame = 0;
}


AnimationPlayer::AnimationPlayer(AnimationClip& animationClip) : m_animationClip(animationClip) 
{
    m_currentFrame = m_animationClip.StartFrame;
}


void AnimationPlayer::Update(float dt)
{
    if (m_animationClip.IsStill)
        return;

    m_timeInCurrentFrame += dt;

    if (m_timeInCurrentFrame <= m_animationClip.FrameDuration)
        return;

    m_currentFrame++;

    if (m_currentFrame >= m_animationClip.FrameCount - m_animationClip.StartFrame)
    {
        if (m_animationClip.Loop)
        {
            m_currentFrame = m_animationClip.StartFrame;
        }
    }

    m_timeInCurrentFrame = 0;
}