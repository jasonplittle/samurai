#include "MobController.hpp"

#include <random>


void MobController::Update(float dt, Character& player, const World& world)
{
    float distance = glm::length(m_mob->Body().Position - player.Body().Position);

    if (distance < 200.f && player.IsAlive())
    {
        m_state = MobState::Attack;
    }

    if (!m_mob->IsAlive())
    {
        m_state = MobState::Idle;
    }

    CharacterIntent intent;

    switch(m_state)
    {
        case MobState::Idle:
            intent = updateIdle(dt);
            break;

        case MobState::Patrol:
            intent = updatePatrol(dt);
            break;

        case MobState::Attack:
            intent = updateAttack(dt, player, distance);
            break;
    }

    m_mob->SetIntent(intent);
}


CharacterIntent MobController::updateIdle(float dt)
{
    m_idleTimer += dt;

    float moveX = 0.f;

    if (m_idleTimer > 2.0f)
    {
        m_state = MobState::Patrol;
        moveX = m_mob->IsFacingRight() ? -0.5f : 0.5f;
        m_idleTimer = 0;
    }

    CharacterIntent intent;
    intent.MoveX = moveX;

    return intent;
}

CharacterIntent MobController::updatePatrol(float dt)
{
    m_patrolTimer += dt;

    float moveX = m_mob->IsFacingRight() ? 0.6f : -0.6f;

    if (m_patrolTimer > 5.0f)
    {
        m_state = MobState::Idle;
        m_patrolTimer = 0;
    }

    CharacterIntent intent;
    intent.MoveX = moveX;

    return intent;
}

CharacterIntent MobController::updateAttack(float dt, Character& player, float distance)
{
    float moveX = player.Body().Position.x < m_mob->Body().Position.x ? -1.f : 1.f;
    bool attack = false;
    int rand = 0;

    static std::mt19937 rng(std::random_device{}());
    

    if (distance < m_mob->Stats().StationaryAttackRange && player.Body().Position.x > m_mob->Body().Position.x == m_mob->IsFacingRight())
    {
        moveX = 0;
        attack = true;

        std::uniform_int_distribution<int> dist(0, 100);
        rand = dist(rng);
    }
    else if (distance < m_mob->Stats().PrimaryAttackRange)
    {
        attack = true;

        std::uniform_int_distribution<int> dist(0, 100);
        rand = dist(rng);
    }
    else if (distance > 200.f)
    {
        m_state = MobState::Patrol;
    }

    if (!player.IsAlive())
    {
        std::cout << "Player is dead" << std::endl;
        m_state = MobState::Patrol;
        attack = false;
    }

    CharacterIntent intent;
    intent.MoveX = moveX;

    if (m_mob->StateMachine().CheckState(StateID::Attacking))
        return intent;

    if (rand > 90)
    {
        intent.Ultimate.Pressed = attack;
    }
    else
    {
        intent.Primary.Pressed = attack;
    }

    return intent;
}
