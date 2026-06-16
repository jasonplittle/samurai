#include "MobController.hpp"



void MobController::Update(float dt, Character& player, const World& world)
{
    float distance = glm::length(m_mob->Body().Position - player.Body().Position);

    if (distance < 200.f)
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

    int moveX = 0;

    if (m_idleTimer > 2.0f)
    {
        m_state = MobState::Patrol;
        moveX = m_mob->IsFacingRight() ? -1 : 1;
        m_idleTimer = 0;
    }

    CharacterIntent intent
    {
        .Jump = false,
        .Down = false,
        .Primary = false,
        .Secondary = false,
        .MoveX = moveX,
    };

    return intent;
}

CharacterIntent MobController::updatePatrol(float dt)
{
    m_patrolTimer += dt;

    int moveX = m_mob->IsFacingRight() ? 1 : -1;

    if (m_patrolTimer > 5.0f)
    {
        m_state = MobState::Idle;
        m_patrolTimer = 0;
    }

    CharacterIntent intent
    {
        .Jump = false,
        .Down = false,
        .Primary = false,
        .Secondary = false,
        .MoveX = moveX,
    };

    return intent;
}

CharacterIntent MobController::updateAttack(float dt, Character& player, float distance)
{
    int moveX = player.Body().Position.x < m_mob->Body().Position.x ? -1 : 1;
    bool attack = false;

    if (distance < 10.f)
    {
        moveX = 0;
    }
    else if (distance < 40.f) // Use mob range stat
    {
        attack = true;
    }
    else if (distance > 200.f)
    {
        m_state = MobState::Patrol;
    }

    CharacterIntent intent
    {
        .Jump = false,
        .Down = false,
        .Primary = attack,
        .Secondary = false,
        .MoveX = moveX,
    };

    return intent;
}