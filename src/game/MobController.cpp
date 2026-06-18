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

    float moveX = 0.f;

    if (m_idleTimer > 2.0f)
    {
        m_state = MobState::Patrol;
        moveX = m_mob->IsFacingRight() ? -1.f : 1.f;
        m_idleTimer = 0;
    }

    CharacterIntent intent
    {
        .MoveX = moveX,
        .Jump = InputButton{false, false, false},
        .Down = InputButton{false, false, false},
        .Primary = InputButton{false, false, false},
        .Secondary = InputButton{false, false, false},
    };

    return intent;
}

CharacterIntent MobController::updatePatrol(float dt)
{
    m_patrolTimer += dt;

    float moveX = m_mob->IsFacingRight() ? 1.f : -1.f;

    if (m_patrolTimer > 5.0f)
    {
        m_state = MobState::Idle;
        m_patrolTimer = 0;
    }

    CharacterIntent intent
    {
        .MoveX = moveX,
        .Jump = InputButton{false, false, false},
        .Down = InputButton{false, false, false},
        .Primary = InputButton{false, false, false},
        .Secondary = InputButton{false, false, false},
    };

    return intent;
}

CharacterIntent MobController::updateAttack(float dt, Character& player, float distance)
{
    float moveX = player.Body().Position.x < m_mob->Body().Position.x ? -2.f : 2.f;
    bool attack = false;

    if (distance < 30.f)
    {
        moveX = 0;
    }
    else if (distance < m_mob->Stats().PrimaryAttackRange)
    {
        attack = true;
    }
    else if (distance > 200.f)
    {
        m_state = MobState::Patrol;
    }

    CharacterIntent intent
    {
        .MoveX = moveX,
        .Jump = InputButton{false, false, false},
        .Down = InputButton{false, false, false},
        .Primary = InputButton{attack, false, false},
        .Secondary = InputButton{false, false, false},
    };

    return intent;
}