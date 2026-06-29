#pragma once

#include "IStateFactory.hpp"

#include "IdleState.hpp"
#include "WalkState.hpp"
#include "RunState.hpp"
#include "JumpState.hpp"
#include "FloatState.hpp"
#include "FallState.hpp"
#include "AttackState.hpp"
#include "HurtState.hpp"
#include "DeathState.hpp"
#include "WallSlideState.hpp"
#include "WallJumpState.hpp"
#include "DashState.hpp"
#include "DoubleJumpState.hpp"


class ArcherStateFactory : public IStateFactory
{
public:
    std::unique_ptr<ICharacterState>
    Create(StateID id) override
    {
        switch (id)
        {
            case StateID::Idle:
                return std::make_unique<IdleState>();

            case StateID::Walk:
                return std::make_unique<WalkState>();

            case StateID::Run:
                return std::make_unique<RunState>();

            case StateID::Jump:
                return std::make_unique<JumpState>();

            case StateID::Float:
                return std::make_unique<FloatState>();
            
            case StateID::Fall:
                return std::make_unique<FallState>();

            case StateID::Attacking:
                return std::make_unique<AttackState>();

            case StateID::Hurt:
                return std::make_unique<HurtState>();

            case StateID::Death:
                return std::make_unique<DeathState>();

            case StateID::Dash:
                return std::make_unique<DashState>();

            default:
                return nullptr;
        }
    }
};
