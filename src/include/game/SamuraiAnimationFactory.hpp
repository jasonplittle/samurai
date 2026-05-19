#pragma once

#include "CharacterAnimation.hpp"


class SamuraiAnimationFactory
{
public:
    static AnimationSet CreateSamuraiAnimations()
    {
        AnimationSet set;
        set.FrameSize = glm::vec2(96, 96);
        set.FrameCenterOffset = glm::vec2(0, -16);

        set.Clips[CharacterState::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 10,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/IDLE.png", set.FrameSize)
        };
        set.Clips[CharacterState::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALK.png", set.FrameSize)
        };
        set.Clips[CharacterState::Attack] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 1.png", set.FrameSize)
        };
        set.Clips[CharacterState::Jump] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP.png", set.FrameSize)
        };
        set.Clips[CharacterState::Fall] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP.png", set.FrameSize)
        };
        set.Clips[CharacterState::JumpStart] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-START.png", set.FrameSize)
        };
        set.Clips[CharacterState::JumpMid] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-TRANSITION.png", set.FrameSize)
        };
        set.Clips[CharacterState::JumpFall] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-FALL.png", set.FrameSize)
        };

        return set;
    }
};
