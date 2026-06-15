#pragma once

#include "CharacterAnimator.hpp"


class SamuraiAnimationFactory
{
public:
    static AnimationSet CreateSamuraiAnimations()
    {
        AnimationSet set;
        set.FrameSize = glm::vec2(96, 96);
        set.FrameCenterOffset = glm::vec2(0, -16);

        set.Clips[Animation::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 10,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/IDLE.png", set.FrameSize)
        };
        set.Clips[Animation::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALK.png", set.FrameSize)
        };
        set.Clips[Animation::Run] =
        {
            .StartFrame = 0,
            .FrameCount = 16,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/RUN.png", set.FrameSize)
        };
        set.Clips[Animation::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 1.png", set.FrameSize)
        };
        set.Clips[Animation::Attack2] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 2.png", set.FrameSize)
        };
        set.Clips[Animation::Attack3] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = 0.1f,
            .Loop = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 3.png", set.FrameSize)
        };
        set.Clips[Animation::Defend] =
        {
            .StartFrame = 0,
            .FrameCount = 5,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEFEND.png", set.FrameSize)
        };
        set.Clips[Animation::Hurt] =
        {
            .StartFrame = 0,
            .FrameCount = 4,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/HURT.png", set.FrameSize)
        };
        set.Clips[Animation::Jump] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-START.png", set.FrameSize)
        };
        set.Clips[Animation::Float] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-TRANSITION.png", set.FrameSize)
        };
        set.Clips[Animation::Fall] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-FALL.png", set.FrameSize)
        };
        set.Clips[Animation::WallContact] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL CONTACT.png", set.FrameSize)
        };
        set.Clips[Animation::WallSlide] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.1f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL SLIDE.png", set.FrameSize)
        };
        set.Clips[Animation::AirAttack] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = 0.1f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/Air ATTACK.png", set.FrameSize)
        };
        set.Clips[Animation::Death] =
        {
            .StartFrame = 0,
            .FrameCount = 9,
            .FrameDuration = 0.2f,
            .Loop = false,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEATH.png", set.FrameSize)
        };
        set.Clips[Animation::Dead] =
        {
            .StartFrame = 8,
            .FrameCount = 9,
            .FrameDuration = 0.2f,
            .Loop = true,
            .FlipX = false,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEATH.png", set.FrameSize)
        };

        return set;
    }
};
