#include "Character.hpp"

#include <iostream>

constexpr float jumpPeakTs = 0.3;
constexpr float jumpPeakHeight = 48;

constexpr float regGrav = (2 * jumpPeakHeight) / (jumpPeakTs * jumpPeakTs);
constexpr float v0 = (2 * jumpPeakHeight) / jumpPeakTs;

constexpr int fastGrav = 3 * regGrav;

const float jumpMidThreshUp = std::sqrt(0.25) * v0;
const float jumpMidThreshDown = std::sqrt(0.15) * v0;


constexpr float walkSpeed = 45;


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

void Character::MoveLeft() 
{ 
    m_isFacingRight = false; 
    m_body.Velocity.x = -walkSpeed; 
};

void Character::MoveRight() 
{ 
    m_isFacingRight = true; 
    m_body.Velocity.x = walkSpeed; 
};

void Character::Update(float dt, bool animationFinished)
{
    // float speedDiff = m_targetSpeed - m_body.Velocity.x;
    // m_body
    // m_rigidbody.Velocity.x += speedDiff * m_acc * dt;

    // std::cout << m_body.Velocity.y << std::endl;

    // if (!m_body.IsGrounded)
    // {
    //     m_state = CharacterState::Fall;
    // }
    // else
    // {
    //     m_state = CharacterState::Idle;
    // }



    switch(m_state)
    {
        case CharacterState::Idle:
        {
            // std::cout << "Idle" << std::endl;

            if (abs(m_body.Velocity.x) > 0)
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

            if (m_body.Velocity.x == 0)
            {
                m_state = CharacterState::Idle;
            }

            if (!m_body.IsGrounded)
            {
                m_state = CharacterState::JumpMid;
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
