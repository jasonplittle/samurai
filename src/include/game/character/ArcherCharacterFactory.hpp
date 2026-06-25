#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Character.hpp"
#include "ArcherAnimationFactory.hpp"
#include "ArcherStateFactory.hpp"
#include "ArcherAbilityFactory.hpp"


class ArcherCharacterFactory
{
public:
    static std::unique_ptr<Character> CreateCharacter(glm::vec2 initPos, IGameplayContext& gameplayContext)
    {
        constexpr float jumpPeakTs = 0.2;
        constexpr float jumpPeakHeight = 48;

        constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
        constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

        constexpr float fastGrav = 1.8 * regGrav;

        constexpr float idleSpeed = 5;
        constexpr float walkSpeed = 100;
        constexpr float runSpeed = 140;

        constexpr float groundedAccel = 8;
        constexpr float groundedDeccel = 13;


        CharacterStats stats
        {
            .MaxHealth = 100,
            .Mass = 2,
            
            .CanJump = true,
            .CanDoubleJump = false,
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

            .WalkAccel = 4,
            .WalkDeccel = 8,

            .RunAccel = 8,
            .RunDeccel = 6,

            .CanWallSlide = false,
            .WallSlideGravity = regGrav / 6.f,

            .MaxHeals = 3,

            .CanRun = false,
        };

        AnimationMap animationMap;
        animationMap[Animation::Fall] = Animation::Jump;
        animationMap[Animation::Float] = Animation::Jump;
        animationMap[Animation::Run] = Animation::Walk;

        CharacterAbilities abilities = CharacterAbilities(std::make_unique<ArcherAbilityFactory>());

        AnimationSetPlayer animator = AnimationSetPlayer(Animation::Idle, ArcherAnimationFactory::CreateAnimations(ArcherColor::Green), animationMap);

        CharacterStateMachine stateMachine = CharacterStateMachine(std::make_unique<ArcherStateFactory>());

        std::unique_ptr<Character> archer = std::make_unique<Character>(initPos, stats, std::move(stateMachine), std::move(animator), std::move(abilities), gameplayContext);
        return archer;
    }
};
