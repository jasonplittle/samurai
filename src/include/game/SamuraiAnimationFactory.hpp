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
            .FrameDuration = 0.2f,
            .Loop = true,
            .Sprite = std::make_unique<Sprite>("resources/samurai/Idle.png", {96, 96}, 0)
        };

        Where to store current frame?
        Sprite ior clip


            // glm::ivec2 spriteSizes = {32, 32};
    // glm::ivec2 spriteSizes = {96, 96};

    // m_attackSprite = std::make_unique<Sprite>("resources/samurai/ATTACK 1.png", spriteSizes, 0);
    // m_hurtSprite = std::make_unique<Sprite>("resources/samurai/HURT.png", spriteSizes, 0);
    // m_idleSprite = std::make_unique<Sprite>("resources/samurai/IDLE.png", spriteSizes, 0);
    // m_runSprite = std::make_unique<Sprite>("resources/samurai/RUN.png", spriteSizes, 0);
    // m_jumpSprite = std::make_unique<Sprite>("resources/samurai/JUMP.png", spriteSizes, 0);


        return set;
    }
};