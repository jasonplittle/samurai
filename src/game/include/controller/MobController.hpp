#pragma once

#include <memory>
#include <queue>
#include <vector>

#include "Character.hpp"
#include "World.hpp"


enum class MobState
{
    Idle,
    Patrol,
    Attack,
};


class MobController
{
public:
    MobController(std::shared_ptr<Character> mob) : m_mob(mob) {};

    void Update(float dt, Character& player, const World& world);

private:
    CharacterIntent updateIdle(float dt);
    CharacterIntent updatePatrol(float dt);
    CharacterIntent updateAttack(float dt, Character& player, float distance);

private:
    std::shared_ptr<Character> m_mob;

    MobState m_state = MobState::Idle;

    float m_idleTimer = 0.f;
    float m_patrolTimer = 0.f;
    float m_attackTimer = 0.f;
};