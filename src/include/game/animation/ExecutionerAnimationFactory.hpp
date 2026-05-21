#pragma once

#pragma once

#include "CharacterAnimation.hpp"


class ExecutionerAnimationFactory
{
public:
    static AnimationSet CreateExecutionerAnimations()
    {
        AnimationSet set;
        set.FrameSize = glm::vec2(130, 92);
        set.FrameCenterOffset = glm::vec2(0, -16);

        set.Clips[CharacterState::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/IDLE.png", set.FrameSize)
        };
        set.Clips[CharacterState::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/WALK.png", set.FrameSize)
        };
        set.Clips[CharacterState::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 1.png", set.FrameSize)
        };
        set.Clips[CharacterState::Attack2] =
        {
            .StartFrame = 0,
            .FrameCount = 8,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 2.png", set.FrameSize)
        };

        return set;
    }
};
