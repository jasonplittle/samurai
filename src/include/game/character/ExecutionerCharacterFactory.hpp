#pragma once

#include <glm/glm.hpp>
#include <memory>

#include "Character.hpp"
#include "ExecutionerAnimationFactory.hpp"
#include "ExecutionerStateFactory.hpp"
#include "ExecutionerAbilityFactory.hpp"


class ExecutionerCharacterFactory
{
public:
    static std::unique_ptr<Character> CreateExecutionerCharacter(glm::vec2 initPos, IGameplayContext& gameplayContext)
    {
        constexpr float jumpPeakTs = 0.3;
        constexpr float jumpPeakHeight = 64;

        constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
        constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;


        CharacterStats stats
        {
            .MaxHealth = 100,
            .Mass = 10,
            
            .CanJump = false,
            .JumpVelocity = 0,
            .Gravity = regGrav,
            .FallGravity = regGrav,
            .FastFallGravity = regGrav,

            .Width = 48,
            .Height = 48,
            .RadiusX = 12,
            .RadiusY = 22,

            .IdleSpeed = 5,
            .WalkSpeed = 30,
            .RunSpeed = 50,

            .WalkAccel = 3,
            .WalkDeccel = 5,

            .RunAccel = 3,
            .RunDeccel = 5,

            .CanWallSlide = false,
            .WallSlideGravity = 0,

            .PrimaryAttackRange = 60.f
        };

        AnimationMap animationMap;
        animationMap[Animation::Fall] = Animation::Idle;
        animationMap[Animation::Float] = Animation::Idle;
        animationMap[Animation::Run] = Animation::Walk;

        
        CharacterAbilities abilities = CharacterAbilities(std::make_unique<ExecutionerAbilityFactory>());

        CharacterAnimator animator = CharacterAnimator(Animation::Idle, ExecutionerAnimationFactory::CreateExecutionerAnimations(), animationMap);

        CharacterStateMachine stateMachine = CharacterStateMachine(std::make_unique<ExecutionerStateFactory>());

        std::unique_ptr<Character> executioner = std::make_unique<Character>(initPos, stats, std::move(stateMachine), std::move(animator), std::move(abilities), gameplayContext);
        return executioner;
    }
};
