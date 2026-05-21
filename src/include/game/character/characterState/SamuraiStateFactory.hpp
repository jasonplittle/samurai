#pragma once

#include "IStateFactory.hpp"

#include "IdleState.hpp"
#include "RunState.hpp"
#include "FallState.hpp"
#include "WalkState.hpp"

class SamuraiStateFactory : public IStateFactory
{
public:
    std::unique_ptr<CharacterState>
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

            case StateID::Fall:
                return std::make_unique<FallState>();

            // case StateID::SwordCombo:
            //     return std::make_unique<SwordComboState>();

            default:
                return nullptr;
        }
    }
};