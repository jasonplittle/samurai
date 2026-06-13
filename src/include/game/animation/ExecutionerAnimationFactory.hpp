#pragma once

#include "CharacterAnimator.hpp"


class ExecutionerAnimationFactory
{
public:
    static AnimationSet CreateExecutionerAnimations()
    {
        AnimationSet set;
        set.FrameSize = glm::vec2(130, 92);
        set.FrameCenterOffset = glm::vec2(0, -4);

        set.Clips[Animation::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/IDLE.png", set.FrameSize)
        };
        set.Clips[Animation::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/WALK.png", set.FrameSize)
        };
        set.Clips[Animation::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 1.png", set.FrameSize)
        };
        set.Clips[Animation::Attack2] =
        {
            .StartFrame = 0,
            .FrameCount = 8,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 2.png", set.FrameSize)
        };
        set.Clips[Animation::Hurt] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/HURT.png", set.FrameSize)
        };
        set.Clips[Animation::Death] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = true,
            .Sprite = std::make_unique<Sprite>("resources/executioner/ATTACK 2.png", set.FrameSize)
        };

        return set;
    }
};
