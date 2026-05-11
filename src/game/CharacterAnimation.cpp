#include "CharacterAnimation.hpp"


CharacterAnimation::CharacterAnimation(CharacterState initState, AnimationSet animationSet) 
    : m_currentState(initState), 
      m_animationSet(std::move(animationSet)) 
{
    m_currentFrame = m_animationSet.Clips.at(m_currentState).StartFrame;
}

void CharacterAnimation::Update(float dt, CharacterState characterState)
{
    m_timeInCurrentFrame += dt;
    m_currentState = characterState;

    if (m_timeInCurrentFrame > m_animationSet.Clips.at(m_currentState).FrameDuration)
    {
        m_currentFrame++;

        if (m_animationSet.Clips.at(m_currentState).Loop && m_currentFrame >= m_animationSet.Clips.at(m_currentState).FrameCount + m_animationSet.Clips.at(m_currentState).StartFrame)
        {
            m_currentFrame = m_animationSet.Clips.at(m_currentState).StartFrame;
        }

        m_timeInCurrentFrame = 0; // Use remained of dt?
    }
}