#pragma once

#include "Animator.hpp"


class ExecutionerAnimationFactory
{
public:
    static AnimationSet CreateAnimations()
    {
        AnimationSet set;
        glm::vec2 frameSize = glm::vec2(130, 92);
        glm::vec2 standardFrameCenterOffset = glm::vec2(0, -4);

        set.Clips[Animation::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/IDLE.png", frameSize)
        };
        set.Clips[Animation::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/WALK.png", frameSize)
        };
        set.Clips[Animation::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 1.png", frameSize)
        };
        set.Clips[Animation::Attack2] =
        {
            .StartFrame = 0,
            .FrameCount = 8,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 2.png", frameSize)
        };
        set.Clips[Animation::Hurt] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/HURT.png", frameSize)
        };
        set.Clips[Animation::Death] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/DEATH.png", frameSize)
        };
        set.Clips[Animation::Dead] =
        {
            .StartFrame = 10,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = true,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/executioner/DEATH.png", frameSize)
        };

        return set;
    }
};
