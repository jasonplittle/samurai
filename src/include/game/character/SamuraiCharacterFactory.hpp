#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Character.hpp"
#include "SamuraiAnimationFactory.hpp"
#include "SamuraiStateFactory.hpp"
#include "SamuraiAbilityFactory.hpp"


class SamuraiCharacterFactory
{
public:
    static std::unique_ptr<Character> CreateSamuraiCharacter(glm::vec2 initPos, IGameplayContext& gameplayContext)
    {
        constexpr float jumpPeakTs = 0.5;
        constexpr float jumpPeakHeight = 128;

        constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
        constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

        constexpr float fastGrav = 3 * regGrav;

        const float jumpMidThreshUp = std::sqrt(0.25) * v0;
        const float jumpMidThreshDown = std::sqrt(0.15) * v0;

        constexpr float idleSpeed = 5;
        constexpr float walkSpeed = 90;
        constexpr float runSpeed = 200;

        constexpr float groundedAccel = 8;
        constexpr float groundedDeccel = 13;
        constexpr float defendDeccel = 20;
        constexpr float defendAccel = 0.8;


        CharacterStats stats
        {
            .MaxHealth = 100,
            .Mass = 2,
            
            .CanJump = true,
            .JumpVelocity = v0,
            .Gravity = regGrav,
            .FallGravity = regGrav * 2,
            .FastFallGravity = regGrav * 4,

            .Width = 32,
            .Height = 32,
            .RadiusX = 8,
            .RadiusY = 14,


            .IdleSpeed = idleSpeed,
            .WalkSpeed = walkSpeed,
            .RunSpeed = runSpeed,

            .WalkAccel = 6,
            .WalkDeccel = 8,

            .RunAccel = 13,
            .RunDeccel = 8,

            .CanWallSlide = true,
            .WallSlideGravity = regGrav / 6.f,
        };


        CharacterAbilities abilities = CharacterAbilities(std::make_unique<SamuraiAbilityFactory>());

        CharacterAnimator animator = CharacterAnimator(Animation::Idle, SamuraiAnimationFactory::CreateSamuraiAnimations(), AnimationMap());

        CharacterStateMachine stateMachine = CharacterStateMachine(std::make_unique<SamuraiStateFactory>());

        std::unique_ptr<Character> samurai = std::make_unique<Character>(initPos, stats, std::move(stateMachine), std::move(animator), std::move(abilities), gameplayContext);
        return samurai;
    }
};
