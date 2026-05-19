#include "Character.hpp"

#include <iostream>

constexpr float jumpPeakTs = 0.3;
constexpr float jumpPeakHeight = 64;

constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

constexpr int fastGrav = 3 * regGrav;

const float jumpMidThreshUp = std::sqrt(0.25) * v0;
const float jumpMidThreshDown = std::sqrt(0.15) * v0;

constexpr float idleSpeed = 5;
constexpr float walkSpeed = 90;
constexpr float runSpeed = 150;

constexpr float groundedAccel = 8;
constexpr float groundedDeccel = 13;
constexpr float defendDeccel = 20;
constexpr float defendAccel = 0.8;

// Todo Constants based on size


Character::Character(glm::vec2 position, glm::vec2 size)
    : m_state(CharacterState::Idle)
{
    m_body.Position = position;
    m_body.Radii.y = size.y * 0.45f;
    m_body.Radii.x = size.x * 0.25f;
    m_body.UseGravity = true;
    m_body.Gravity = regGrav;
}


void Character::Jump()
{
    if (m_body.IsGrounded)
    {
        m_state = CharacterState::JumpStart;
        m_body.Velocity.y = v0;
    }
}

void Character::MoveDown()
{
    if (!m_body.IsGrounded)
    {
        m_state = CharacterState::JumpFall;
        m_body.Gravity = fastGrav;
    }
}

void Character::Defend()
{
    if (m_body.IsGrounded && m_defendCooldownTimer >= 1.0f)
    {
        m_state = CharacterState::Defend;
        m_defendCooldownTimer = 0;

        const float speedDif = -m_body.Velocity.x;
        m_body.Acceleration.x = speedDif * defendDeccel;
    }
}

void Character::MoveLeft() 
{ 
    m_isFacingRight = false; 

    const float speedDif = -runSpeed - m_body.Velocity.x;
    m_body.Acceleration.x = speedDif * (m_state == CharacterState::Defend ? defendAccel : groundedAccel);
};

void Character::MoveRight() 
{ 
    m_isFacingRight = true; 

    const float speedDif = runSpeed - m_body.Velocity.x;
    m_body.Acceleration.x = speedDif * (m_state == CharacterState::Defend ? defendAccel : groundedAccel);
};

void Character::Idle()
{
    const float speedDif = -m_body.Velocity.x;
    m_body.Acceleration.x = speedDif * groundedDeccel;
}

void Character::Update(float dt, bool animationFinished)
{
    m_defendCooldownTimer += dt;

    switch(m_state)
    {
        case CharacterState::Idle:
        {
            // std::cout << "Idle" << std::endl;

            if (std::abs(m_body.Velocity.x) > idleSpeed)
            {
                m_state = CharacterState::Walk;
            }

            if (!m_body.IsGrounded)
            {
                m_state = CharacterState::JumpMid;
            }

            break;
        }
        case CharacterState::Walk:
        {
            // std::cout << "Walk" << std::endl;

            if (std::abs(m_body.Velocity.x) <= idleSpeed && !m_body.IsWalled)
            {
                m_state = CharacterState::Idle;
            }

            if (!m_body.IsGrounded)
            {
                m_state = CharacterState::JumpMid;
            }

            if (std::abs(m_body.Velocity.x) > walkSpeed)
            {
                m_state = CharacterState::Run;
            } 

            break;
        }
        case CharacterState::Run:
        {

            // if (m_body.Velocity.x == 0 && !m_body.IsWalled)
            // {
            //     m_state = CharacterState::Idle;
            // }

            if (!m_body.IsGrounded)
            {
                m_state = CharacterState::JumpMid;
            }

            if (std::abs(m_body.Velocity.x) <= walkSpeed)
            {
                m_state = CharacterState::Walk;
            }

            break;
        }
        case CharacterState::Attack:
        {
            if (animationFinished)
            {
                m_state = CharacterState::Idle;
            }
            break;
        }
        case CharacterState::Defend:
        {
            if (animationFinished)
            {
                m_state = CharacterState::Idle;
            }
            break;
        }
        case CharacterState::JumpStart:
        {
            // std::cout << "Start" << std::endl;

            if (m_body.Velocity.y < jumpMidThreshUp)
            {
                m_state = CharacterState::JumpMid;
            }

            break;
        }
        case CharacterState::JumpMid:
        {
            // std::cout << "Mid" << std::endl;

            if (m_body.Velocity.y < -jumpMidThreshDown && animationFinished) // Loop count at whole loop
            {
                m_state = CharacterState::JumpFall;
            }

            if (m_body.IsGrounded && animationFinished)
            {
                m_state = CharacterState::Idle;
            }

            break;
        }
        case CharacterState::JumpFall:
        {
            // std::cout << "Fall" << std::endl;
            if (m_body.IsGrounded)
            {
                m_state = CharacterState::Idle;
                m_body.Gravity = regGrav;
            }

            break;
        }
    }
}
