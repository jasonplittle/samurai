#include "CharacterAnimator.hpp"


CharacterAnimator::CharacterAnimator(Animation initAnimation, AnimationSet animationSet) 
    : m_currentAnimation(initAnimation), 
      m_animationSet(std::move(animationSet)) 
{
    m_currentFrame = m_animationSet.Clips.at(m_currentAnimation).StartFrame;
}

void CharacterAnimator::Play(Animation animation)
{
    if (animation != m_currentAnimation)
    {
        m_currentFrame = m_animationSet.Clips.at(animation).StartFrame;
        m_isFinished = false;
    }

    m_currentAnimation = animation;
}

void CharacterAnimator::Update(float dt)
{
    m_timeInCurrentFrame += dt;

    if (m_timeInCurrentFrame <= m_animationSet.Clips.at(m_currentAnimation).FrameDuration)
        return;

    m_currentFrame++;

    if (m_currentFrame >= m_animationSet.Clips.at(m_currentAnimation).FrameCount + m_animationSet.Clips.at(m_currentAnimation).StartFrame)
    {
        if (m_animationSet.Clips.at(m_currentAnimation).Loop)
        {
            m_currentFrame = m_animationSet.Clips.at(m_currentAnimation).StartFrame;
        }
        
        m_isFinished = true;
    }

    m_timeInCurrentFrame = 0;
}