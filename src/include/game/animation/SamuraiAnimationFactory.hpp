#pragma once

#include "Animator.hpp"


class SamuraiAnimationFactory
{
public:
    static AnimationSet CreateAnimations()
    {
        AnimationSet set;
        
        glm::vec2 standardFrameCenterOffset = glm::vec2(0, -16);
        glm::vec2 frameSize = glm::vec2(96, 96);
        float frameRate = 0.07f;


        set.Clips[Animation::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 10,
            .FrameDuration = frameRate,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/IDLE.png", frameSize)
        };
        set.Clips[Animation::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 12,
            .FrameDuration = frameRate,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALK.png", frameSize)
        };
        set.Clips[Animation::Run] =
        {
            .StartFrame = 0,
            .FrameCount = 16,
            .FrameDuration = 0.05,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/RUN.png", frameSize)
        };
        set.Clips[Animation::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 1.png", frameSize)
        };
        set.Clips[Animation::Attack2] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 2.png", frameSize)
        };
        set.Clips[Animation::Attack3] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/ATTACK 3.png", frameSize)
        };
        set.Clips[Animation::Defend] =
        {
            .StartFrame = 0,
            .FrameCount = 5,
            .FrameDuration = 0.1,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEFEND.png", frameSize)
        };
        set.Clips[Animation::Hurt] =
        {
            .StartFrame = 0,
            .FrameCount = 4,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/HURT.png", frameSize)
        };
        set.Clips[Animation::Jump] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = frameRate,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-START.png", frameSize)
        };
        set.Clips[Animation::Float] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.12,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-TRANSITION.png", frameSize)
        };
        set.Clips[Animation::Fall] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = frameRate,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/JUMP-FALL.png", frameSize)
        };
        set.Clips[Animation::WallContactLeft] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.11f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = glm::vec2(10, -4),
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL CONTACT.png", frameSize)
        };
        set.Clips[Animation::WallContactRight] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.11f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = glm::vec2(-10, -4),
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL CONTACT.png", frameSize)
        };
        set.Clips[Animation::WallSlideLeft] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.09f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = glm::vec2(10, -4),
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL SLIDE.png", frameSize)
        };
        set.Clips[Animation::WallSlideRight] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = 0.09f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = glm::vec2(-10, -4),
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL SLIDE.png", frameSize)
        };
        set.Clips[Animation::WallJump] =
        {
            .StartFrame = 0,
            .FrameCount = 3,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/WALL JUMP.png", frameSize)
        };
        set.Clips[Animation::AirAttack] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/Air ATTACK.png", frameSize)
        };
        set.Clips[Animation::Death] =
        {
            .StartFrame = 0,
            .FrameCount = 9,
            .FrameDuration = 0.15f,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEATH.png", frameSize)
        };
        set.Clips[Animation::Dead] =
        {
            .StartFrame = 8,
            .FrameCount = 9,
            .FrameDuration = 0.15f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DEATH.png", frameSize)
        };
        set.Clips[Animation::Dash] =
        {
            .StartFrame = 0,
            .FrameCount = 4,
            .FrameDuration = 0.05,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/DASH.png", frameSize)
        };
        set.Clips[Animation::Throw] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.08,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/samurai/THROW.png", frameSize)
        };

        return set;
    }
};
