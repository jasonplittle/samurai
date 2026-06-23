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
    static std::unique_ptr<Character> CreateCharacter(glm::vec2 initPos, IGameplayContext& gameplayContext)
    {
        constexpr float jumpPeakTs = 0.4;
        constexpr float jumpPeakHeight = 96;

        constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
        constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

        constexpr float fastGrav = 1.8 * regGrav;

        constexpr float idleSpeed = 5;
        constexpr float walkSpeed = 120;
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
            .CanDoubleJump = true,
            .JumpVelocity = v0,
            .Gravity = regGrav,
            .FloatGravity = regGrav * 0.65,
            .FallGravity = regGrav * 1.8,
            .FastFallGravity = regGrav * 4.5,

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

            .CanRun = true,
        };


        CharacterAbilities abilities = CharacterAbilities(std::make_unique<SamuraiAbilityFactory>());

        AnimationPlayer animator = AnimationPlayer(Animation::Idle, SamuraiAnimationFactory::CreateAnimations(), AnimationMap());

        CharacterStateMachine stateMachine = CharacterStateMachine(std::make_unique<SamuraiStateFactory>());

        std::unique_ptr<Character> samurai = std::make_unique<Character>(initPos, stats, std::move(stateMachine), std::move(animator), std::move(abilities), gameplayContext);
        return samurai;
    }
};
