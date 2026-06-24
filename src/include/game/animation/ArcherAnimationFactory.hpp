#pragma once

#include "Animator.hpp"


enum class ArcherColor
{
    Blue,
    Red,
    Green
};


class ArcherAnimationFactory
{
public:
    static AnimationSet CreateAnimations(ArcherColor color)
    {
        AnimationSet set;
        
        glm::vec2 standardFrameCenterOffset = glm::vec2(0, -8);
        glm::vec2 frameSize = glm::vec2(96, 80);
        float frameRate = 0.07f;

        std::string colorPath;

        switch (color)
        {
            case ArcherColor::Blue:
                colorPath = "BLUE";
                break;

            case ArcherColor::Red:
                colorPath = "RED";
                break;

            case ArcherColor::Green:
                colorPath = "GREEN";
                break;
        }

        set.Clips[Animation::Idle] =
        {
            .StartFrame = 0,
            .FrameCount = 14,
            .FrameDuration = frameRate,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/IDLE.png", frameSize)
        };
        set.Clips[Animation::Walk] =
        {
            .StartFrame = 0,
            .FrameCount = 8,
            .FrameDuration = 0.1,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/RUN.png", frameSize)
        };
        set.Clips[Animation::Attack1] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/ATTACK.png", frameSize)
        };
        set.Clips[Animation::Defend] =
        {
            .StartFrame = 0,
            .FrameCount = 6,
            .FrameDuration = 0.1,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/BLOCK.png", frameSize)
        };
        set.Clips[Animation::Hurt] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/HURT.png", frameSize)
        };
        set.Clips[Animation::Jump] =
        {
            .StartFrame = 0,
            .FrameCount = 7,
            .FrameDuration = 0.07,
            .Loop = false,
            .LeaveOnLastFrame = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/JUMP.png", frameSize)
        };
        set.Clips[Animation::AirAttack] =
        {
            .StartFrame = 0,
            .FrameCount = 10,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/RUN.png", frameSize)
        };
        set.Clips[Animation::Death] =
        {
            .StartFrame = 0,
            .FrameCount = 11,
            .FrameDuration = 0.15f,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/DEATH.png", frameSize)
        };
        set.Clips[Animation::Dead] =
        {
            .StartFrame = 10,
            .FrameCount = 11,
            .FrameDuration = 0.15f,
            .Loop = true,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/DEATH.png", frameSize)
        };
        set.Clips[Animation::Dash] =
        {
            .StartFrame = 0,
            .FrameCount = 5,
            .FrameDuration = 0.05,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/DASH.png", frameSize)
        };
        set.Clips[Animation::SpecialAttack] =
        {
            .StartFrame = 0,
            .FrameCount = 22,
            .FrameDuration = frameRate,
            .Loop = false,
            .FlipX = false,
            .FrameCenterOffset = standardFrameCenterOffset,
            .FrameSize = frameSize,
            .Sprite = std::make_unique<Sprite>("resources/archer/"+colorPath+"/SPECIAL ATTACK.png", frameSize)
        };

        return set;
    }
};
