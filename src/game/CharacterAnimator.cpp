#include "CharacterAnimator.hpp"

#include <iostream>


CharacterAnimator::CharacterAnimator(Animation initAnimation, AnimationSet animationSet, AnimationMap animationMap) 
    : m_currentAnimation(initAnimation), 
      m_animationSet(std::move(animationSet)),
      m_animationMap(animationMap)
{
    m_currentFrame = m_animationSet.Clips.at(m_currentAnimation).StartFrame;
}

void CharacterAnimator::Play(Animation animation)
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
    }

    m_currentAnimation = nextAnimation;
    m_timeInCurrentFrame = 0.f;
}

void CharacterAnimator::Update(float dt)
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