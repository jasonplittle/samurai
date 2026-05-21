#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Character.hpp"
#include "SamuraiAnimationFactory.hpp"
#include "SamuraiStateFactory.hpp"


class SamuraiCharacterFactory
{
public:
    static std::unique_ptr<Character> CreateSamuraiCharacter(glm::vec2 initPos)
    {
        constexpr float jumpPeakTs = 0.3;
        constexpr float jumpPeakHeight = 64;

        constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
        constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

        constexpr int fastGrav = 3 * regGrav;

        const float jumpMidThreshUp = std::sqrt(0.25) * v0;
        const float jumpMidThreshDown = std::sqrt(0.15) * v0;

        constexpr float idleSpeed = 5;
        constexpr float walkSpeed = 90;
        constexpr float runSpeed = 150;

        constexpr float groundedAccel = 8;
        constexpr float groundedDeccel = 13;
        constexpr float defendDeccel = 20;
        constexpr float defendAccel = 0.8;


        CharacterStats stats
        {
            .MaxHealth = 100,
            
            .MaxJumpVelocity = v0,
            .Gravity = regGrav,

            .Width = 32,
            .Height = 32,

            .WalkSpeed = walkSpeed,
            .RunSpeed = runSpeed  
        };


        CharacterAnimator animator = CharacterAnimator(Animation::Idle, SamuraiAnimationFactory::CreateSamuraiAnimations());

        CharacterStateMachine stateMachine = CharacterStateMachine(std::make_unique<SamuraiStateFactory>());

        std::unique_ptr<Character> samurai = std::make_unique<Character>(initPos, stats, stateMachine, animator);
        return samurai;
    }
};
