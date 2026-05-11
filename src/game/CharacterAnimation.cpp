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

    if (characterState != m_currentState)
    {
        m_currentFrame = m_animationSet.Clips.at(characterState).StartFrame;
        m_isFinished = false;
    }

    m_currentState = characterState;

    if (m_timeInCurrentFrame > m_animationSet.Clips.at(m_currentState).FrameDuration)
    {
        m_currentFrame++;

        if (m_currentFrame >= m_animationSet.Clips.at(m_currentState).FrameCount + m_animationSet.Clips.at(m_currentState).StartFrame)
        {
            if (m_animationSet.Clips.at(m_currentState).Loop)
            {
                m_currentFrame = m_animationSet.Clips.at(m_currentState).StartFrame;
            }
            else
            {
                m_isFinished = true;
            }
        }

        m_timeInCurrentFrame = 0;
    }
}