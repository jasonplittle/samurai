#pragma once

#include "CharacterAnimation.hpp"


class SamuraiAnimationFactory
{
public:
    static AnimationSet CreateSamuraiAnimations()
    {
        AnimationSet set;

        set.Clips[CharacterState::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 10,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/IDLE.png", glm::vec2(96, 96))
        };
        set.Clips[CharacterState::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALK.png", glm::vec2(96, 96))
        };
        set.Clips[CharacterState::Attack] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 1.png", glm::vec2(96, 96))
        };
        set.Clips[CharacterState::Jump] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP.png", glm::vec2(96, 96))
        };

        return set;
    }
};